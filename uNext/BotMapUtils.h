#pragma once

#include <utility>

class BotMapUtils
{
public:
	/**
		Checks if there is a hole on this position which will make mario fall and die.
	*/
	static bool isHoleInMap(int fXPos, int fYPos);

	/**
		Checks if the player would collide with the bottom in this position.
	*/
	static bool doesPlayerHaveCollisionBottom();

	/**
		Checks if the player would collide with the bottom in this position.
	*/
	static bool doesPlayerHaveCollisionBottom(int fXPos, int fYPos);

	/**
		Checks if the player would collide with an object from his right, and it is not a pipe.
	*/
	static bool doesPlayerHaveCollisionRight(int fXPos, int fYPos);

	/**
		Returns the coordinates of the block containing the player.
	*/
	static std::pair<int, int> getPlayerBlockCoordinates();

	/// the size of a block in pixels.
	static const int BLOCK_SIZE;

private:
};

