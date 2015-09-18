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
	MovePicker mPicker(board, ply, hashMove);
	int bestMove = NO_MOVE;
	
	for (int i=0; i < 7; i++) {
			
		int move = NO_MOVE;
		if (board.get_height(i) - 7 * i <= 5) {
			move = board.get_height(i);
		}
		if (move == NO_MOVE) {
			continue;
		}

		//int move = mPicker.getNextMove();
		
		//if (move == NO_MOVE) {
			//break;
		//}

		board.MakeMove(move);
		int score = -Solve(NON_ROOT, board, ply + 1, -beta, -alpha, depth - 1);
		board.UnmakeMove();
		nodesVisited++;
		movesMade++;

		if (score >= beta) {
			TTEntry newEntry = {board.get_key(), L_BOUND, depth, score, move};
			TranspositionTable.storeTTable(board.get_key(), newEntry);
			//updateKillers(move, ply);
			//updateHistory(depth, ply, move);

			if (movesMade == 1) {
				fh1++;
			} else {
				fh++;
			}
			return score;
		} else if (score > bestScore) {
			bestScore = score;
			bestMove = move;
			if (score > alpha) {
				alpha = score;
				raisedAlpha = true;
			}
		}
		 
	}

	if (raisedAlpha) {
		TTEntry newEntry = {board.get_key(), EXACT, depth, alpha, bestMove};
		TranspositionTable.storeTTable(board.get_key(), newEntry);
	} else {
		TTEntry newEntry = {board.get_key(), U_BOUND, depth, bestScore, NO_MOVE};
		TranspositionTable.storeTTable(board.get_key(), newEntry);
	}
	return bestScore;
}

void updateKillers (int move, int ply) {
	if (move != killerTable[ply][0] && move != NO_MOVE) {
		killerTable[ply][1] = killerTable[ply][0];
		killerTable[ply][0] = move;
	}
}

void updateHistory (int depth, int ply, int move) {
	historyTable[ply & 1][move] += depth;
	if (historyTable[ply & 1][move] > 100000000) {
		for (int i = 0; i < 49; i++) {
			historyTable[ply & 1][i] /= 2;
		}
	}
}

MovePicker::MovePicker(Position& inputBoard, int ply, int hashMove) 
	:board(inputBoard)
{
	numberOfMoves = moveIndex = 0;
	this->ply = ply;
	this->hashMove = hashMove;
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
			if (lowestFreeInCol == killerTable[ply][0]) {
				score += KILLER_0_SCORE;
			} else if (lowestFreeInCol == killerTable[ply][1]) {
				score += KILLER_1_SCORE;
			}
			score += historyTable[ply & 1][lowestFreeInCol];

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

