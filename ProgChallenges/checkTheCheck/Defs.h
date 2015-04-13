#ifndef __DEFS__
#define __DEFS__

//#define DEBUG(...) printf( __VA_ARGS__ )
#define DEBUG(...)


namespace Chess {

enum PieceType {
	TypePawn = 1,
	TypeKnight,
	TypeBishop,
	TypeRook,
	TypeQueen,
	TypeKing,
	INVALID
};

enum PieceColor {
	White = -1,
	Black = 1
};

}

#endif
