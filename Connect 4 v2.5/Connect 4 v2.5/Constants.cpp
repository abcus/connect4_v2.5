#include <iostream>
#include <string>
#include "Constants.h"
#include "Position.h"

uint64_t pieceZobrist[2][49];

void initSearchConstants() {
	for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 49; j++) {
            pieceZobrist[i][j] = randomGenerator();
        }
    }
	
    /*for (int i = 0; i < MAX_DEPTH; i++) {
        for (int j = 0; j < 2; j++) {
            Solve.killerTable[i, j] = -1;
        }
    }*/
}

uint64_t randomGenerator() {
	uint64_t randomNum;
	randomNum = rand();
	randomNum = (randomNum << 32) | rand();
	return randomNum;
}

void DrawBoard(Position& inputBoard) {
	 for (int i = 0; i < 6; i++) {
            if (i == 0) {
                std::cout << "+---+---+---+---+---+---+---+" << std::endl;
            } else if (i >= 1) {
                std::cout << "+---+---+---+---+---+---+---+" << std::endl;
            }
                
            for (int j = 0; j < 7; j++) {
                int shiftNumber = 5 - i + (7*j);
                std::string piece;
                if ((0x1ULL << shiftNumber & inputBoard.get_arrayOfBitboard(0)) != 0) {
                    piece = "O";
                } else if ((0x1ULL << shiftNumber & inputBoard.get_arrayOfBitboard(1)) != 0) {
                    piece = "X";
                } else {
                    piece = " ";
                }

                std::cout<<"| " << piece << " ";
            }
            std::cout<< "|" << std::endl;;
        }
        std::cout<< "+---+---+---+---+---+---+---+" << std::endl;
        std::cout<< "  1   2   3   4   5   6   7" << std::endl;
        std::cout<< "" << std::endl;
        std::cout << "Key: " << inputBoard.get_key() << std::endl;
        std::cout << std::endl;
}



