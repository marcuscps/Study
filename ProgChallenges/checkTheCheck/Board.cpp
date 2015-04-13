#include "Defs.h"
#include "Board.h"
#include "Piece.h"

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <list>
#include <string>

using namespace std;
using namespace Chess;

Board::Board() {
	for (int ii = 0; ii < SIZE; ++ii) {
		for (int jj = 0; jj < SIZE; ++jj) {
			m_Pieces[ii][jj] = NULL;
		}
	}

	m_WhiteKing = NULL;
	m_BlackKing = NULL;
}

Board::~Board() {
	for (int ii = 0; ii < SIZE; ++ii) {
		for (int jj = 0; jj < SIZE; ++jj) {
			if (m_Pieces[ii][jj] != NULL) {
				delete m_Pieces[ii][jj];
			}
		}
	}
}

bool Board::readBoard() {
	int counter = 0;
	char c;
	PieceColor color;

	for (int ii = 0; ii < SIZE; ++ii) {
		for (int jj = 0; jj < SIZE; ++jj) {
			if (scanf("%c", &c) != 1) {
				return false;
			}

			if (c >= 'A' && c <= 'Z') {
				color = White;
				c = c - 'A' + 'a';
			} else {
				color = Black;
			}

			++counter;
			switch (c) {
				case 'p': addPiece(new   Pawn(ii, jj, color)); break;
				case 'n': addPiece(new Knight(ii, jj, color)); break;
				case 'b': addPiece(new Bishop(ii, jj, color)); break;
				case 'r': addPiece(new   Rook(ii, jj, color)); break;
				case 'q': addPiece(new  Queen(ii, jj, color)); break;
				case 'k': addPiece(new   King(ii, jj, color)); break;
				case '.':
				default:
					--counter;
					break;
			}
		}

		scanf("\n");
	}

	return counter > 0;
}

void Board::addPiece(Piece *piece) {
	int line = piece->getLine();
	int column = piece->getColumn();

	m_Pieces[line][column] = piece;
	if (piece->getType() == TypeKing) {
		if (piece->getColor() == White) {
			m_WhiteKing = piece;
		} else {
			m_BlackKing = piece;
		}
	}
}

Piece * Board::getPiece(int line, int column) const {
	return m_Pieces[line][column];
}

Piece * Board::checkCheck() const {
	for (int ii = 0; ii < SIZE; ++ii) {
		for (int jj = 0; jj < SIZE; ++jj) {
			Piece *piece = m_Pieces[ii][jj];
			if (piece != NULL && piece->isChecking(this)) {
				return piece;
			}
		}
	}
	return NULL;
}

