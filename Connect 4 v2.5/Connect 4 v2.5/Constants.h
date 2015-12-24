#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>
#include "Position.h"

const int WIDTH = 7, HEIGHT = 6, H1 = 7, H2 = 8, SIZE = 42, SIZE1 = 49;
const uint64_t ALL1 = 0x1FFFFFFFFFFFF, COL1 = 0x7F, BOTTOM = 0x40810204081, TOP = 0x1020408102040, ALL = ALL1 ^ TOP;
const int WIN = 100, DRAW = 0;
const int MAX_DEPTH = 42, INF = 999999999;
extern uint64_t pieceZobrist[2][49];
const int TT_SIZE = 15485867, BUCKET_SIZE = 4;
const int EXACT = 1, L_BOUND = 2, U_BOUND = 3;
const int ROOT = 1, NON_ROOT = 2;
extern struct TTEntry EMPTY_ENTRY;
extern int positionScore[7];
static int KILLER_0_SCORE = 100000000, KILLER_1_SCORE = 80000000, HASH_MOVE_SCORE = 500000000;
const int NO_MOVE = -1;

void initSearchConstants();
uint64_t randomGenerator();
void DrawBoard(Position& inputBoard);
void PerftTest();
void PerftDivide();
uint64_t perft(int depth, Position& inputBoard);

#endif