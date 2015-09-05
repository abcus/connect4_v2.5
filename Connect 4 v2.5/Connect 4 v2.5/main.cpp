#include <iostream>
#include <string>
#include "Position.h"
#include "Constants.h"
using namespace std;

static void InitializeSearch();

int main() {
	initSearchConstants();
	PerftTest();
	//InitializeSearch();
	return 0;
}

static void InitializeSearch() {
	std::cout << "Enter position to solve: " << std::endl;
	std::string inputString;
	getline(std::cin, inputString);
	Position test(inputString);
	DrawBoard(test);
}
