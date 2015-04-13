#include <iostream>
#include <cstdio>
#include <algorithm>
#include <list>

#include "Defs.h"
#include "PieceBehavior.h"
#include "Piece.h"
#include "Board.h"

using namespace std;
using namespace Chess;

PieceBehavior::~PieceBehavior() {
}

bool PawnBehavior::isChecking(const Board *board, const Piece *piece) const {
	DEBUG("PAWN behavior\n");

	int tLine = piece->getLine() + ((piece->getColor() == White) ? -1 : 1);
	if (tLine >= Board::SIZE || tLine < 0) {
		DEBUG("  DOES NOT CHECK - TOP/BOTTOM!\n");
		return false;
	}

	int column = piece->getColumn();
	if (column > 0) {
		const Piece *target = board->getPiece(tLine, column - 1);
		if (target != NULL && target->isInCheck(piece)) {
			DEBUG("  CHECKS!\n");
			return true;
		}
	}

	if (column < Board::SIZE - 1) {
		const Piece *target = board->getPiece(tLine, column + 1);
		if (target != NULL && target->isInCheck(piece)) {
			DEBUG("  CHECKS!\n");
			return true;
		}
	}

	DEBUG("  DOES NOT CHECK!\n");
	return false;
}

bool KnightBehavior::isChecking(const Board *board, const Piece *piece) const {
	DEBUG("NIGHT behavior\n");

	int dLine[]   = { 1,  2,  2,  1, -1, -2, -2, -1 };
	int dColumn[] = {-2, -1,  1,  2,  2,  1, -1, -2 };

	int line = piece->getLine();
	int column = piece->getColumn();

	for (int kk = 0; kk < 8; ++kk) {
		int l = line + dLine[kk];
		int c = column + dColumn[kk];

		if (l >= 0 && l < Board::SIZE && c >= 0 && c < Board::SIZE) {
			Piece *target = board->getPiece(l, c);
			if (target != NULL && target->isInCheck(piece)) {
				DEBUG("  CHECKS!\n");
				return true;
			}
		}
	}

	DEBUG("  DOES NOT CHECK!\n");
	return false;
}

bool BishopBehavior::isChecking(const Board *board, const Piece *piece) const {
	DEBUG("BISHOP behavior\n");

	int dLine[]   = {-1, -1,  1,  1 };
	int dColumn[] = {-1,  1,  1, -1 };

	int line = piece->getLine();
	int column = piece->getColumn();

	for (int kk = 0; kk < 4; ++kk) {
		for (int l = line, c = column; 
			l >= 0 && l < Board::SIZE && c >= 0 && c < Board::SIZE;
			l += dLine[kk], c += dColumn[kk])
		{
			Piece *target = board->getPiece(l, c);
			if (target != NULL && target->isInCheck(piece)) {
				DEBUG("  CHECKS!\n");
				return true;
			}
		}
	}

	DEBUG("  DOES NOT CHECK!\n");
	return false;
}

bool RookBehavior::isChecking(const Board *board, const Piece *piece) const {
	DEBUG("ROOK behavior\n");

	int dLine[]   = { 0, -1,  0,  1 };
	int dColumn[] = {-1,  0,  1,  0 };

	int line = piece->getLine();
	int column = piece->getColumn();

	for (int kk = 0; kk < 4; ++kk) {
		for (int l = line, c = column;
				l >= 0 && l < Board::SIZE && c >= 0 && c < Board::SIZE;
				l += dLine[kk], c += dColumn[kk])
		{
			Piece *target = board->getPiece(l, c);
			if (target != NULL && target->isInCheck(piece)) {
				DEBUG("  CHECKS!\n");
				return true;
			}
		}
	}

	DEBUG("  DOES NOT CHECK!\n");
	return false;
}

bool KingBehavior::isChecking(const Board *board, const Piece *piece) const {
	DEBUG("KING behavior\n");

	int dLine[]   = { 0, -1, -1, -1,  0,  1,  1,  1 };
	int dColumn[] = {-1, -1,  0,  1,  1,  1,  0, -1 };

	int line = piece->getLine();
	int column = piece->getColumn();

	for (int kk = 0; kk < 8; ++kk) {
		int l = line + dLine[kk];
		int c = column + dColumn[kk];

		if (l >= 0 && l < Board::SIZE && c >= 0 && c < Board::SIZE) {
			Piece *target = board->getPiece(l, c);
			if (target != NULL && target->isInCheck(piece)) {
				DEBUG("  CHECKS!\n");
				return true;
			}
		}
	}
	
	DEBUG("  DOES NOT CHECK!\n");
	return false;
}

