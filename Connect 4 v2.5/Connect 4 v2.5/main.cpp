#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "Position.h"
#include "Constants.h"
#include "TTable.h"
#include "Solve.h"
using namespace std;

static void InitializeSearch();

int main() {
	
	initSearchConstants();
	//PerftTest();
	InitializeSearch();
	return 0;
}

static void InitializeSearch() {
	std::cout << "Enter position to solve: " << std::endl;
	std::string inputString;
	getline(std::cin, inputString);
	Position board(inputString);
	DrawBoard(board);
	std::cout << ((board.get_nPlies() & 1) == 0  ? "White: " : "Black: ");
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	int evaluation = Solve(ROOT, board, 0, -INF, INF, (MAX_DEPTH - board.get_nPlies()));
	
	if (evaluation == 0) {
		std::cout << "draw";
	} else if (evaluation >= 0) {
		std:cout << "win in " << (WIN - evaluation);
	} else {
		std::cout <<"loss in " << (WIN + evaluation);
	}
	std::cout << "\t\tBest move: Column " << (get_PV_Move(board.get_key())/ 7 + 1) << std::endl;
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	uint64_t elapsed_milliseconds = (elapsed_seconds.count() * 1000) + 1;
	std::cout.imbue(std::locale(""));
	std::cout << "Nodes: " << nodesVisited << "\t\tTime: " << elapsed_milliseconds << " milliseconds\t\tNPS: " << (nodesVisited/(elapsed_milliseconds + 1)) * 1000 << std::endl;
	std::cout << "FH1: " << (fh1 / (fh1 + fh)) * 100 << std::endl;
}
