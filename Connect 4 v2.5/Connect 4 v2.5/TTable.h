#ifndef TTABLE_H
#define TTABLE_H

#include <cstdint>
#include "Constants.h"

struct TTEntry {
	uint64_t key;
	int flag;
	int depth;
	int evaluationScore;
	int move;
};

class TTable {
	public:
		TTable();
		void storeTTable(uint64_t key, TTEntry entry);
		TTEntry probeTTable(uint64_t key);
		
	private:
		TTEntry* transpositionTable;
};

#endif