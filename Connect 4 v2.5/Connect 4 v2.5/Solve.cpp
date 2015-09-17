#include <iostream>
#include <string>
#include "Position.h"
#include "Constants.h"
#include "TTable.h"
#include "Solve.h"

TTable TranspositionTable;
double fh1 = 0, fh = 0;
int killerTable [MAX_DEPTH][2];
int historyTable [2][49];
uint64_t nodesVisited = 0;

int Solve (int nodeType, Position& board, int ply, int alpha, int beta, int depth) {
	
	if (board.HasWon(board.get_arrayOfBitboard((board.get_nPlies() - 1) & 1))) {
		return -WIN + ply;
	} else if (board.get_nPlies() == 42) {
		return DRAW;
	}
	
	TTEntry entry = TranspositionTable.probeTTable(board.get_key());

	if (entry.flag == EXACT
		|| entry.flag == L_BOUND && entry.evaluationScore >= beta
		|| entry.flag == U_BOUND && entry.evaluationScore <= alpha) {

		if (entry.evaluationScore >= beta) {
			updateKillers(entry.move, ply);
		}
		return entry.evaluationScore;
	}

	int hashMove = (entry.flag == L_BOUND && entry.evaluationScore < beta) ? entry.move : NO_MOVE;
	int bestScore = -INF;
	int movesMade = 0;
	bool raisedAlpha = false;


	return -70;

	/*
	Position testP("");
	MovePicker test(testP, 2, 2);
	std:: cout << test.getNextMove() << std::endl;
	std:: cout << test.getNextMove() << std::endl;
	std:: cout << test.getNextMove() << std::endl;
	std:: cout << test.getNextMove() << std::endl;
	std:: cout << test.getNextMove() << std::endl;
	std:: cout << test.getNextMove() << std::endl;
	std:: cout << test.getNextMove() << std::endl;
	std:: cout << test.getNextMove() << std::endl;
	*/
	

	//TTable test;
	//TTEntry testEntry = {343434, 99, 100, 101, 102};
	//test.storeTTable(343434, testEntry);
	//TTEntry test2Entry = {343434, 30, 31, 32, 33};
	//test.storeTTable(343434, test2Entry);
	//TTEntry probe = test.probeTTable(343434);
}

void updateKillers (int move, int ply) {

}

void updateHistory (int depth, int ply, int move) {

}

MovePicker::MovePicker(Position& inputBoard, int ply, int hashMove) 
	:board(inputBoard)
{
	numberOfMoves = moveIndex = 0;
	this->ply = ply;
	this->hashMove = hashMove;
	board.MakeMove(21);
	DrawBoard(board);
	moveList = moveGenerator();
}

Move* MovePicker::moveGenerator() {
	static Move moveList [7]; 
	
	for (int i = 0; i < 7; i++) {
		int lowestFreeInCol = board.get_height(i);
		if (lowestFreeInCol - 7 * i <= 5) {
			int score = (CENTRAL_COLUMN_SCORE - DISTANCE_PENALTY * abs(i - 3));
			if (hashMove != NO_MOVE && lowestFreeInCol == hashMove) {
				score += HASH_MOVE_SCORE;
			}
			//killers
			//history

			moveList[i].move = lowestFreeInCol;
			moveList[i].score = score;
			numberOfMoves ++;
		}
	}
	return moveList;
}

int MovePicker::getNextMove() {
	
	while (moveIndex < numberOfMoves) {

		int maxScore = -INF;
        int maxPosition = -1;
		for (int i = moveIndex; i < numberOfMoves; i++) {
                        
			if (moveList[i].score > maxScore) {
				maxScore = (moveList[i].score);
                maxPosition = i;
			}
		}
        Move moveTemp = moveList[moveIndex];
        moveList[moveIndex] = moveList[maxPosition];
        moveList[maxPosition] = moveTemp;

        int move = (moveList[moveIndex].move);
                    
        moveIndex++;
		return move;   
	}
    return NO_MOVE;
}

