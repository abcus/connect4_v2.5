#include <iostream>
#include <string>
#include "Position.h"
#include "Constants.h"
#include "TTable.h"

TTable::TTable() {
	 transpositionTable = new TTEntry[TT_SIZE + BUCKET_SIZE];
}

void TTable::storeTTable(uint64_t key, TTEntry entry) {
	int index = (int) (key % TT_SIZE);

	// If entry in bucket has same hash key, then replace
    for (int i = index; i < index + BUCKET_SIZE; i++) {
        if (transpositionTable[i].key == key) {
            transpositionTable[i] = entry;
			return;
        }
    }
    // If there is an empty spot in the bucket, then store it there
    for (int i = index; i < index + BUCKET_SIZE; i++) {
        if (transpositionTable[i].key == 0) {
            transpositionTable[i] = entry;
            return;
        }
    }
    // If all spots full, then replace entry with lowest depth
    int shallowestDepth = INF;
    int indexOfShallowestEntry = -1;
    for (int i = index; i < index + BUCKET_SIZE; i++) {
        if (transpositionTable[i].depth < shallowestDepth) {
            shallowestDepth = transpositionTable[i].depth;
            indexOfShallowestEntry = i;
        }
    }
    transpositionTable[indexOfShallowestEntry] = entry;
}

TTEntry TTable::probeTTable(uint64_t key) {
	int index = (int) (key % TT_SIZE);
	
	for (int i = index; i < index + BUCKET_SIZE; i++) {
		if (transpositionTable[i].key == key) {
			return transpositionTable[i];
		}
	}
	return EMPTY_ENTRY;
}