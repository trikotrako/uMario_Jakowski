#pragma once
class BotKeyUtils
{
public:
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

