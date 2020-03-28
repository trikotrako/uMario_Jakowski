#pragma once

#include <queue>
#include <SDL_events.h>

enum class Move {
	NOTHING,
	GO_RIGHT,
	STOP_GO_RIGHT,
	JUMP,
};

class BotPlayer final
{
public:
	BotPlayer() = default;
	~BotPlayer() = default;

	/**
		Makes the next moves.
	*/
	static void pressKeysUsingBot();

	/**
		Decide the next moves to make.
	*/
	static void decideNextMoves();

private:

	static std::queue<Move> s_movesQueue;

	/**
		Jumps.
	*/
	static void jump();

	/**
		Jumps and then goes right in order to get over an obstacle.
	*/
	static void jumpAndGoRight();

	/**
		Continue to the right.
	*/
	static void goRight();

	/**
		Continue to the right.
	*/
	static void stopGoingRight();

	/**
		return true if already in the process of a jump.
	*/
	static bool isAlreadyJumping();

	/**
		return true if the player is already going right.
	*/
	static bool isAlreadyGoingRight();

	/**
		Simulates a key down event
	*/
	static void pressKey(int key);

	/**
		Simulates a key up event
	*/
	static void releaseKey(int key);
};

