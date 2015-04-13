#include <iostream>
#include <cstdio>
#include <algorithm>
#include <list>
#include <string>

#include "Defs.h"
#include "Board.h"
#include "Piece.h"

using namespace std;
using namespace Chess;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	unsigned int t;
	for (t = 1; ; ++t) {
		Board board;
		if (board.readBoard() == false) {
			break;
		}

		Piece *checker = board.checkCheck();
		if (checker != NULL) {
			PieceColor color = checker->getColor() == White ? Black : White;
			printf("Game #%u: %s king is in check.\n", t, Piece::ColorToString(color).c_str());
		}
	}

	return 0;
}

