#include "Core.h"
#include "BotMapUtils.h"

const int BotMapUtils::BLOCK_SIZE = 32;

bool BotMapUtils::isHoleInMap(int fXPos, int fYPos)
{
	// check from the given y until the ground, because of gravity
	for (int y = fYPos; y < CCFG::GAME_HEIGHT; y += BLOCK_SIZE / 2) {
		if (doesPlayerHaveCollisionBottom(fXPos, y)) {
			return false;
		}
	}

	return true;
}

bool BotMapUtils::doesPlayerHaveCollisionBottom()
{
	return doesPlayerHaveCollisionBottom(CCore::getMap()->getPlayer()->getXPos() - (int)CCore::getMap()->getXPos(), CCore::getMap()->getPlayer()->getYPos());
}

bool BotMapUtils::doesPlayerHaveCollisionBottom(int fXPos, int fYPos)
{
	// code copied from Player::playerPhysics

	if (!CCore::getMap()->checkCollisionLB(fXPos + 2, fYPos + 2, CCore::getMap()->getPlayer()->getHitBoxY(), true) &&
		!CCore::getMap()->checkCollisionRB(fXPos - 2, fYPos + 2, CCore::getMap()->getPlayer()->getHitBoxX(), CCore::getMap()->getPlayer()->getHitBoxY(), true)) {
		// no collision on that block when falling on it
		return false;
	}

	return true;
}

bool BotMapUtils::doesPlayerHaveCollisionRight(int fXPos, int fYPos)
{
	// code copied from Player::checkCollisionCenter
	Vector2* v = CCore::getMap()->getPlayer()->getBlockRC((float)fXPos, (float)fYPos);
	auto block = CCore::getMap()->getBlock(CCore::getMap()->getMapBlock(v->getX(), v->getY())->getBlockID());
	delete v;
	if (block->getCollision()) {
		// block has collision. check that it's not a pipe because we would like to go through pipes.
		switch (block->getBlockID()) {
		case 36: case 38: case 60: case 62: case 103: case 105: case 118: case 120: // Pipe (copied from Map::blockUse)
			return false;
		default:
			return true;
		}
	}

	return false;
}

std::pair<int, int> BotMapUtils::getPlayerBlockCoordinates()
{
	auto blockId = CCore::getMap()->getBlockID(CCore::getMap()->getPlayer()->getXPos() - (int)CCore::getMap()->getXPos(), CCore::getMap()->getPlayer()->getYPos());

	auto x = blockId->getX();
	auto y = blockId->getY();
	delete blockId;
	return std::make_pair(x, y);
}
