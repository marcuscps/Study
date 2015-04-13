#include <iostream>
#include <cstdio>
#include <algorithm>
#include <list>

#include "Defs.h"
#include "Piece.h"
#include "PieceBehavior.h"
#include "Board.h"

using namespace std;
using namespace Chess;

Piece::Piece(PieceType type, int line, int column, PieceColor color) :
	m_Type(type), m_Line(line), m_Column(column), m_Color(color) {
}

Piece::~Piece() {
	for(BehaviorList::iterator it = m_Behaviors.begin(); it != m_Behaviors.end(); ++it) {
		delete *it;
	}
}

PieceType Piece::getType() const {
	return m_Type;
}

int Piece::getLine() const {
	return m_Line;
}

int Piece::getColumn() const {
	return m_Column;
}

PieceColor Piece::getColor() const {
	return m_Color;
}

string Piece::ColorToString(PieceColor color) {
	return color == White ? "white" : "black";
}

bool Piece::isChecking(const Board *board) const {
	DEBUG("Checking piece at %d, %d\n", m_Line, m_Column);

	for(BehaviorList::const_iterator it = m_Behaviors.begin(); it != m_Behaviors.end(); ++it) {
		PieceBehavior *behavior = *it;
		if (behavior->isChecking(board, this) == true) {
			return true;
		}
	}
	return false;
}

bool Piece::isInCheck(const Piece *attacker) const {
	return false;
}

void Piece::addBehavior(PieceBehavior *behavior) {
	m_Behaviors.push_back(behavior);
}


Pawn::Pawn(int x, int y, PieceColor color) :
	Piece(TypePawn, x, y, color)
{
	DEBUG("PAWN created: %d, %d, %d\n", x, y, color);
	addBehavior(new PawnBehavior());
}

Knight::Knight(int x, int y, PieceColor color) :
	Piece(TypeKnight, x, y, color)
{
	DEBUG("KNIGHT created: %d, %d, %d\n", x, y, color);
	addBehavior(new KnightBehavior());
}

Bishop::Bishop(int x, int y, PieceColor color) :
	Piece(TypeBishop, x, y, color)
{
	DEBUG("BISHOP created: %d, %d, %d\n", x, y, color);
	addBehavior(new BishopBehavior());
}

Rook::Rook(int x, int y, PieceColor color) :
	Piece(TypeRook, x, y, color)
{
	DEBUG("ROOK created: %d, %d, %d\n", x, y, color);
	addBehavior(new RookBehavior());
}

Queen::Queen(int x, int y, PieceColor color) :
	Piece(TypeQueen, x, y, color)
{
	DEBUG("QUEEN created: %d, %d, %d\n", x, y, color);
	addBehavior(new BishopBehavior());
	addBehavior(new RookBehavior());
}

King::King(int x, int y, PieceColor color) :
	Piece(TypeKing, x, y, color)
{
	DEBUG("KING created: %d, %d, %d\n", x, y, color);
	addBehavior(new KingBehavior());
}

bool King::isInCheck(const Piece *attacker) const {
	return attacker->getColor() != m_Color;
}

