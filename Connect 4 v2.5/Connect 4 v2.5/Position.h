#ifndef POSITION_H
#define POSITION_H

#include <cstdint>

class Position {

	public:
		Position(std::string inputString);
		int get_nPlies();
		uint64_t get_arrayOfBitboard(int colour);
		int get_moveHistory(int ply);
		int get_height(int column);
		uint64_t get_key();
		void MakeMove(int move);
		void UnmakeMove();
		bool HasWon(uint64_t inputBoard);

	private:
		int nPlies; // keeps track of the number of plies that have been played to get to the current position
		uint64_t key;
		uint64_t arrayOfBitboard[2]; // stores the bitboards for the white and black players and the combined bitboard
		int moveHistory[42]; // stores the history of the moves (represented by what column 0-7 the move was played in)
		int height[7]; // stores the index of the lowest unoccupied square in each column
};

struct Move {
	int move;
	int score;
};

#endif