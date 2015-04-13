#ifndef __PIECE_H__
#define __PIECE_H__

#include <list>
#include <string>

#include "Defs.h"

namespace Chess {

class Board;
class PieceBehavior;

class Piece {
protected:
	typedef std::list<PieceBehavior *> BehaviorList;

	PieceType m_Type;
	int m_Line, m_Column;
	PieceColor m_Color;
	BehaviorList m_Behaviors;

public:

	Piece(PieceType type, int line, int column, PieceColor color);

	virtual ~Piece();

	PieceType getType() const;
	int getLine() const;
	int getColumn() const;
	PieceColor getColor() const;

	static std::string ColorToString(PieceColor color);

	bool isChecking(const Board *board) const;

	virtual bool isInCheck(const Piece *attacker) const;

protected:

	void addBehavior(PieceBehavior *behavior);

};

class Pawn : public Piece {
public:
	Pawn(int line, int column, PieceColor color);
};

class Knight : public Piece {
public:
	Knight(int line, int column, PieceColor color);
};

class Bishop : public Piece {
public:
	Bishop(int line, int column, PieceColor color);
};

class Rook : public Piece {
public:
	Rook(int line, int column, PieceColor color);
};

class Queen : public Piece {
public:
	Queen(int line, int column, PieceColor color);
};

class King : public Piece {
public:
	King(int line, int column, PieceColor color);
	bool isInCheck(const Piece *attacker) const;
};

}

#endif
