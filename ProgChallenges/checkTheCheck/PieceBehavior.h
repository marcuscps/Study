#ifndef __PIECE_BEHAVIOR_H__
#define __PIECE_BEHAVIOR_H__

#include "Defs.h"

namespace Chess {

class Piece;
class Board;

class PieceBehavior {
public:
	virtual ~PieceBehavior();

	virtual bool isChecking(const Board *board, const Piece *piece) const = 0;
};


class PawnBehavior : public PieceBehavior {
public:
	bool isChecking(const Board *board, const Piece *piece) const;
};


class KnightBehavior : public PieceBehavior {
public:
	bool isChecking(const Board *board, const Piece *piece) const;
};


class BishopBehavior : public PieceBehavior {
public:
	bool isChecking(const Board *board, const Piece *piece) const;
};


class RookBehavior : public PieceBehavior {
public:
	bool isChecking(const Board *board, const Piece *piece) const;
};


class KingBehavior : public PieceBehavior {
public:
	bool isChecking(const Board *board, const Piece *piece) const;
};

}

#endif
