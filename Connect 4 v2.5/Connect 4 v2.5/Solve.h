#ifndef SOLVE_H
#define SOLVE_H

#include "Constants.h"

int Solve (int nodeType, Position& board, int ply, int alpha, int beta, int depth);
int get_PV_Move(uint64_t key);
void updateKillers (int move, int ply);
void updateHistory (int depth, int ply, int move);

extern int killerTable [MAX_DEPTH][2];
extern uint64_t nodesVisited;
extern double fh1, fh;

class MovePicker {

	public:
		MovePicker(Position& inputBoard, int ply, int hashMove);
		int getNextMove();

	private:
		Position board;
		int ply;
		Move moveList[7];
		int moveIndex;
		int numberOfMoves;
		int hashMove;
		void moveGenerator();
};

#endif