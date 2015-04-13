#ifndef __BOARD_H__
#define __BOARD_H__

#include "Defs.h"

namespace Chess {

class Piece;

class Board {
public:
	static const int SIZE = 8;

private:

	Piece *m_Pieces[SIZE][SIZE];
	Piece *m_WhiteKing;
	Piece *m_BlackKing;

public:

	Board();

	~Board();

	bool readBoard();

	void addPiece(Piece *piece);

	Piece * getPiece(int line, int column) const;

	Piece * checkCheck() const;

};

}

#endif
