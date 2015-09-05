#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
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

void PerftTest() {
	for (int i=1; i < 14; i++) {
		Position test("");
		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();
		uint64_t nodeCount = perft(i, test);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		uint64_t elapsed_milliseconds = (elapsed_seconds.count() * 1000) + 1;
		std::cout.imbue(std::locale(""));
		std::cout << "Depth: " << i << "\t\tNodes: " << nodeCount << "\t\tTime: " << elapsed_milliseconds << "\t\tNPS: " << nodeCount/elapsed_milliseconds * 1000 << std::endl;
	}
}

uint64_t perft (int depth, Position& inputBoard) {
	uint64_t nodes = 0;
    if (inputBoard.HasWon(inputBoard.get_arrayOfBitboard((inputBoard.get_nPlies()-1) & 1)) || inputBoard.get_nPlies() == 42) {
        return 1;
    } else if (depth == 1) {
        for (int i = 0; i < 7; i++) {
            if (inputBoard.get_height(i) - 7 * i <= 5) {
                nodes++;
            }
        }
        return nodes;
    }
	for (int i = 0; i < 7; i++) {
        if (inputBoard.get_height(i) - 7 * i <= 5) {
            inputBoard.MakeMove(inputBoard.get_height(i));
            nodes += perft(depth - 1, inputBoard);
            inputBoard.UnmakeMove();
        }
    }
	return nodes;
}



