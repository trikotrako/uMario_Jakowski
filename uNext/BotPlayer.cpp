
#include <tuple>
#include <algorithm>

#include "Core.h"
#include "BotKeyUtils.h"
#include "BotMapUtils.h"
#include "BotPlayer.h"

const int MID_JUMP_STATE = 1;
const int HIGH_JUMP_STATE = 2;

const int JUMP_SPEED = 4;
const int GO_RIGHT_SPEED = 4;

BotPlayer::BotPlayer()
{
	m_movesQueue.push(Move::GO_RIGHT); // start the game with going right.
}

void BotPlayer::pressKeysUsingBot()
{
	if (CCFG::getMM()->eGame != CCFG::getMM()->getViewID()) {
		// we don't want to press buttons while not in game view.
		return;
	}

	if (HIGH_JUMP_STATE == CCore::getMap()->getPlayer()->jumpState && CCFG::keySpace) {
		// after the jump is complete we must release the space key so we can jump again.
		BotKeyUtils::releaseKey(CCFG::keyIDSpace);
		return;
	}

	if (!BotMapUtils::doesPlayerHaveCollisionBottom()) {
		// for simplicity, we don't decide on new moves while we're in the air.
		return;
	}

	if (m_movesQueue.empty()) {
		decideNextMoves();
	}

	const auto currentMove = m_movesQueue.front();
	m_movesQueue.pop();

	switch (currentMove) {
	case Move::GO_RIGHT:
		if (!BotKeyUtils::isAlreadyGoingRight()) {
			BotKeyUtils::pressKey(CCFG::keyIDD);
		}
		break;
	case Move::STOP_GO_RIGHT:
		if (BotKeyUtils::isAlreadyGoingRight()) {
			BotKeyUtils::releaseKey(CCFG::keyIDD);
		}
		break;
	case Move::JUMP:
		// we want to get to jumpState==2, by pressing space for a long period of time.
		if (2 > CCore::getMap()->getPlayer()->jumpState && !CCFG::keySpace) {
			BotKeyUtils::pressKey(CCFG::keyIDSpace);
		}
	case Move::NOTHING:
	default:
		break;
	}
}

void BotPlayer::decideNextMoves()
{
	int playerX = CCore::getMap()->getPlayer()->getXPos() - (int)CCore::getMap()->getXPos();
	int playerY = CCore::getMap()->getPlayer()->getYPos();

	for (int x = playerX; x < std::min((playerX + 40), (CCFG::GAME_WIDTH - (int)CCore::getMap()->getXPos())); x += BotMapUtils::BLOCK_SIZE / 2) {
		// if there is a hole then we would like to jump
		if (BotMapUtils::isHoleInMap(x, playerY)) {
			m_movesQueue.push(Move::JUMP);
			return;
		}

		// if there is a barrier we would like to jump over it
		if (BotMapUtils::doesPlayerHaveCollisionRight(x, playerY)) {
			m_movesQueue.push(Move::JUMP);
			return;
		}
	}

	// if there is nothing special then just go right.
	m_movesQueue.push(Move::GO_RIGHT);
}
