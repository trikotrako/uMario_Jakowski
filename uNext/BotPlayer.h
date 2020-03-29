#pragma once

#include <queue>

enum class Move {
	NOTHING,
	GO_RIGHT,
	STOP_GO_RIGHT,
	JUMP,
};

class BotPlayer final
{
public:
	BotPlayer();
	~BotPlayer() = default;

	/**
		Makes the next moves.
	*/
	void pressKeysUsingBot();

	/**
		Decide the next moves to make.
	*/
	void decideNextMoves();

private:
	/// the queue of our moves 
	std::queue<Move> m_movesQueue;
};

