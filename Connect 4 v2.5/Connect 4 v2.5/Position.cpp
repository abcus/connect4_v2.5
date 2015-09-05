#include <iostream>
#include <string>
#include "Position.h"
#include "Constants.h"
	
	Position::Position(std::string inputString) {
		nPlies = 0;
		key = 0x1ULL;
		arrayOfBitboard[0] = arrayOfBitboard[1] = 0x0ULL; 
		for (int i= 0; i < 42; i++) {
			moveHistory[i] = NO_MOVE;
		}
		for (int i = 0; i < 7; i++) {
            height[i] = 7*i;
        }
		if (inputString.empty() == false) {
			for (int i = 0; i < inputString.size(); i++) {
				MakeMove(height[inputString[i] - '1']);
			}
		}
	}

	void Position::MakeMove(int move) {
		moveHistory[nPlies] = move;
        arrayOfBitboard[nPlies & 1] ^= (0x1ULL << move);
        key ^= pieceZobrist[nPlies & 1][move];
		
        height[move/7]++;
        nPlies++;
	}

	void Position::UnmakeMove() {
		nPlies--;
        int lastMove = moveHistory[nPlies];
        height[lastMove/7]--;
        key ^= pieceZobrist[nPlies & 1][lastMove];
        arrayOfBitboard[nPlies & 1] ^= (0x1ULL << lastMove);
        moveHistory[nPlies] = 0;
	}

	bool Position::HasWon(uint64_t inputBoard) {
		// checks diagonal 
        uint64_t temp = inputBoard & (inputBoard >> HEIGHT);
        if ((temp & (temp >> 2 * HEIGHT)) != 0) {
            return true;
        }
        // checks horizontal -
        temp = inputBoard & (inputBoard >> H1);
        if ((temp & (temp >> 2 * H1)) != 0) {
            return true;
        }
        //checks diagonal /
        temp = inputBoard & (inputBoard >> H2);
        if ((temp & (temp >> 2 * H2)) != 0) {
            return true;
        }
        // checks vertical |
        temp = inputBoard & (inputBoard >> 1);
        return (temp & (temp >> 2)) != 0;
	}

	int Position::get_nPlies() {
		return nPlies;
	}

	uint64_t Position::get_arrayOfBitboard(int colour) {
		return arrayOfBitboard[colour];
	}

	int Position::get_moveHistory(int ply) {
		return moveHistory[ply];
	}

	int Position::get_height(int column) {
		return height[column];
	}

	uint64_t Position::get_key() {
		return key;
	}
