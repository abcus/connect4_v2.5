#include <iostream>
#include "Position.h"
#include "Constants.h"
using namespace std;

int main() {
	initSearchConstants();
	std::cout << pieceZobrist[0][0] << std::endl;
	Position test;
	DrawBoard(test);
	return 0;
}