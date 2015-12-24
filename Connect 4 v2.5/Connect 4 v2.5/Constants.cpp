#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "Constants.h"
#include "Position.h"
#include "TTable.h"
#include "Solve.h"


uint64_t pieceZobrist[2][49] = { 
	{0x79AD695501E7D1E8UL,	0x8249A47AEE0E41F7UL,	0x637A7780DECFC0D9UL,	0x19FC8A768CF4B6D4UL,	0x7BCBC38DA25A7F3CUL,	0x5093417AA8A7ED5EUL,	0x07FB9F855A997142UL,	0x5355F900C2A82DC7UL,
				0xE99D662AF4243939UL,	0xA49CD132BFBF7CC4UL,	0x0CE26C0B95C980D9UL,	0xBB6E2924F03912EAUL,	0x24C3C94DF9C8D3F6UL,	0xDABF2AC8201752FCUL,	0xF145B6BECCDEA195UL,	0x14ACBAF4777D5776UL,
				0xF9B89D3E99A075C2UL,	0x70AC4CD9F04F21F5UL,	0x9A85AC909A24EAA1UL,	0xEE954D3C7B411F47UL,	0x72B12C32127FED2BUL,	0x54B3F4FA5F40D873UL,	0x8535F040B9744FF1UL,	0x27E6AD7891165C3FUL,
				0x8DE8DCA9F03CC54EUL,	0xFF07F64EF8ED14D0UL,	0x092237AC237F3859UL,	0x87BF02C6B49E2AE9UL,	0x1920C04D47267BBDUL,	0xAE4A9346CC3F7CF2UL,	0xA366E5B8C54F48B8UL,	0x87B3E2B2B5C907B1UL,
				0x6304D09A0B3738C4UL,	0x4F80F7A035DAFB04UL,	0x9A74ACB964E78CB3UL,	0x1E1032911FA78984UL,	0x5BFEA5B4712768E9UL,	0x390E5FB44D01144BUL,	0xB3F22C3D0B0B38EDUL,	0x9C1633264DB49C89UL,
				0x7B32F7D1E03680ECUL,	0xEF927DBCF00C20F2UL,	0xDFD395339CDBF4A7UL,	0x6503080440750644UL,	0x1881AFC9A3A701D6UL,	0x506AACF489889342UL,	0x5B9B63EB9CEFF80CUL,	0x2171E64683023A08UL,
				0xEDE6C87F8477609DUL},
	{0x3BBA57B68871B59DUL,	0xDF1D9F9D784BA010UL,	0x94061B871E04DF75UL,	0x9315E5EB3A129ACEUL,	0x08BD35CC38336615UL,	0xFE9A44E9362F05FAUL,	0x78E37644E7CAD29EUL,	0xC547F57E42A7444EUL,
				0x4F2A5CB07F6A35B3UL,	0xA2F61BB6E437FDB5UL,	0xA74049DAC312AC71UL,	0x336F52F8FF4728E7UL,	0xD95BE88CD210FFA7UL,	0xD7F4F2448C0CEB81UL,	0xF7A255D83BC373F8UL,	0xD2B7ADEEDED1F73FUL,
				0x4C0563B89F495AC3UL,	0x18FCF680573FA594UL,	0xFCAF55C1BF8A4424UL,	0x39B0BF7DDE437BA2UL,	0xF3A678CAD9A2E38CUL,	0x7BA2484C8A0FD54EUL,	0x16B9F7E06C453A21UL,	0x87D380BDA5BF7859UL,
				0x35CAB62109DD038AUL,	0x32095B6D4AB5F9B1UL,	0x3810E399B6F65BA2UL,	0x9D1D60E5076F5B6FUL,	0x7A1EE967D27579E2UL,	0x68CA39053261169FUL,	0x8CFFA9412EB642C1UL,	0x40E087931A00930DUL,
				0x9D1DFA2EFC557F73UL,	0x52AB92BEB9613989UL,	0x528F7C8602C5807BUL,	0xD941ACA44B20A45BUL,	0x4361C0CA3F692F12UL,	0x513E5E634C70E331UL,	0x77A225A07CC2C6BDUL,	0xA90B24499FCFAFB1UL,
				0x284C847B9D887AAEUL,	0x56FD23C8F9715A4CUL,	0x0CD9A497658A5698UL,	0x5A110C6058B920A0UL,	0x04208FE9E8F7F2D6UL,	0x7A249A57EC0C9BA2UL,	0x1D1260A51107FE97UL,	0x722FF175F572C348UL,
				0x5E11E86D5873D484UL},
								};
struct TTEntry EMPTY_ENTRY = {0, 0, 0, 0, -1};

void initSearchConstants() {
	/*for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 49; j++) {
            pieceZobrist[i][j] = randomGenerator();
        }
    }*/
	
    for (int i = 0; i < MAX_DEPTH; i++) {
        for (int j = 0; j < 2; j++) {
            killerTable[i][j] = -1;
        }
    }
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
	for (int i=1; i < 42; i++) {
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

void PerftDivide() {
	Position test("");
	for (int i=0; i < 7; i++) {
		if (test.get_height(i) - 7 * i <= 5) {
			test.MakeMove(test.get_height(i));
			uint64_t nodeCount = perft (7, test);
			std::cout.imbue(std::locale(""));
			std::cout << (i + 1) << "\t\t" << nodeCount << std::endl;
			test.UnmakeMove();
		}
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



