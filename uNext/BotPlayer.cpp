
#include "Core.h"
#include "BotPlayer.h"

const int MID_JUMP_STATE = 1;
const int HIGH_JUMP_STATE = 2;

std::queue<Move> BotPlayer::s_movesQueue;

void BotPlayer::pressKeysUsingBot()
{
	if (CCFG::getMM()->eGame != CCFG::getMM()->getViewID()) {
		// we don't want to press buttons while not in game view.
		return;
	}

	if (HIGH_JUMP_STATE == CCore::oMap->getPlayer()->jumpState && CCFG::keySpace) {
		releaseKey(CCFG::keyIDSpace);
		return;
	}

	if (s_movesQueue.empty()) {
		decideNextMoves();
	}

	const auto currentMove = s_movesQueue.front();
	s_movesQueue.pop();

	switch (currentMove) {
	case Move::GO_RIGHT:
		if (!isAlreadyGoingRight()) {
			pressKey(CCFG::keyIDD);
		}
		break;
	case Move::STOP_GO_RIGHT:
		if (isAlreadyGoingRight()) {
			releaseKey(CCFG::keyIDD);
		}
		break;
	case Move::JUMP:
		// we want to get to jumpState==2, by pressing space for a long period of time.
		if (2 > CCore::oMap->getPlayer()->jumpState && !CCFG::keySpace) {
			pressKey(CCFG::keyIDSpace);
		}
	case Move::NOTHING:
	default:
		break;
	}
}

void BotPlayer::decideNextMoves()
{
	s_movesQueue.push(Move::GO_RIGHT);
	s_movesQueue.push(Move::JUMP);
}

void BotPlayer::jump()
{
	pressKey(CCFG::keyIDSpace);
	releaseKey(CCFG::keyIDSpace);
}

void BotPlayer::jumpAndGoRight()
{
	stopGoingRight();
	pressKey(CCFG::keyIDSpace);
	goRight();
	releaseKey(CCFG::keyIDSpace);
}

void BotPlayer::goRight()
{
	if (isAlreadyGoingRight()) {
		return;
	}

	pressKey(CCFG::keyIDD);
}

void BotPlayer::stopGoingRight()
{
	if (!isAlreadyGoingRight()) {
		return;
	}

	releaseKey(CCFG::keyIDD);
}

bool BotPlayer::isAlreadyJumping()
{
	if (1 == CCore::oMap->getPlayer()->jumpState || CCFG::keySpace) {
		return true;
	}

	return false;
}

bool BotPlayer::isAlreadyGoingRight()
{
	if (CCore::keyDPressed) {
		return true;
	}

	return false;
}

void BotPlayer::pressKey(int key)
{
	SDL_Event sdlEvent;
	sdlEvent.type = SDL_KEYDOWN;
	sdlEvent.key.keysym.sym = key;
	SDL_PushEvent(&sdlEvent);
}

void BotPlayer::releaseKey(int key)
{
	SDL_Event sdlEvent;
	sdlEvent.type = SDL_KEYUP;
	sdlEvent.key.keysym.sym = key;
	SDL_PushEvent(&sdlEvent);
}
