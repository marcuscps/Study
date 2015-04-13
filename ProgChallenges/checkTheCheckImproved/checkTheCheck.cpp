#include <iostream>
#include <cstdio>
#include <algorithm>
#include <list>
#include <string>

using namespace std;


//#define DEBUG(...) printf( __VA_ARGS__ )
#define DEBUG(...)


class Board {
public:
	static const int SIZE = 8;

	enum Color {
		White = -1,
		Black = 1
	};

private:

	char m_Pieces[SIZE][SIZE];
	int m_WKLine, m_WKCol;
	int m_BKLine, m_BKCol;

public:

	static string ColorToString(Color color) {
		return color == White ? "white" : "black";
	}

	static Color GetColor(char piece) {
		return (piece >= 'A' && piece <= 'Z') ? White : Black;
	}


public:

	Board() :
		m_WKLine(-1), m_WKCol(-1),
		m_BKLine(-1), m_BKCol(-1)
	{
		DEBUG("Board constructor...\n");
		for (int lin = 0; lin < SIZE; ++lin) {
			fill(m_Pieces[lin], m_Pieces[lin] + SIZE, 0);
		}
	}

	bool readBoard() {
		DEBUG("Reading board...\n");

		int counter = 0;
		char c;

		DEBUG("BOARD:\n");
		DEBUG("  01234567\n");
		for (int lin = 0; lin < SIZE; ++lin) {
			DEBUG("%d ", lin);
			for (int col = 0; col < SIZE; ++col) {
				if (scanf("%c", &c) != 1) {
					return false;
				}

				if (c != '.') {
					++counter;
					m_Pieces[lin][col] = c;

					if (c == 'K') {
						m_WKLine = lin;
						m_WKCol  = col;
					} else if (c == 'k') {
						m_BKLine = lin;
						m_BKCol  = col;
					}
					DEBUG("%c", m_Pieces[lin][col]);
				} else {
					DEBUG(".");
				}
			}
			scanf("\n");
			DEBUG("\n");
		}

		return counter > 0;
	}

	bool checkCheck(Color *color, int *lin, int *col) const {
		if (m_WKLine != -1 && m_WKCol != -1) {
			DEBUG("Checking White king (%d, %d)...\n", m_WKLine, m_WKCol);
			if (	isPawnChecking(   m_WKLine, m_WKCol, lin, col) ||
					isKnightChecking( m_WKLine, m_WKCol, lin, col) ||
					isBishopChecking( m_WKLine, m_WKCol, lin, col) ||
					isRookChecking(   m_WKLine, m_WKCol, lin, col) ||
					isKingChecking(   m_WKLine, m_WKCol, lin, col)) {
				if (color) {
					*color = White;
				}
				return true;
			}
		}

		if (m_BKLine != -1 && m_BKCol != -1) {
			DEBUG("Checking Black king (%d, %d)...\n", m_BKLine, m_BKCol);
			if (	isPawnChecking(   m_BKLine, m_BKCol, lin, col) ||
					isKnightChecking( m_BKLine, m_BKCol, lin, col) ||
					isBishopChecking( m_BKLine, m_BKCol, lin, col) ||
					isRookChecking(   m_BKLine, m_BKCol, lin, col) ||
					isKingChecking(   m_BKLine, m_BKCol, lin, col)) {
				if (color) {
					*color = Black;
				}
				return true;
			}
		}

		return false;
	}

private:

	bool isPawnChecking(int lin, int col, int *cLin, int *cCol) const {
		DEBUG("PAWN behavior\n");

		char king = m_Pieces[lin][col];
		char expected;
		int l;
		int c;
		if (king == 'K') {
			expected = 'p';
			l = lin + White;
		} else {
			expected = 'P';
			l = lin + Black;
		}

		if (l >= SIZE || l < 0) {
			DEBUG("  DOES NOT CHECK - TOP/BOTTOM!\n");
			return false;
		}

		c = col - 1;
		if (c >= 0) {
			char piece = m_Pieces[l][c];
			if (piece == expected) {
				DEBUG("  CHECKS (%d, %d) = %c!\n", l, c, piece);
				*cLin = l;
				*cCol = c;
				return true;
			} else {
				DEBUG("  DOES NOT CHECK (%d, %d) = %c!\n", l, c, piece);
			}
		}

		c = col + 1;
		if (c < SIZE) {
			char piece = m_Pieces[l][c];
			if (piece == expected) {
				DEBUG("  CHECKS (%d, %d) = %c!\n", l, c, piece);
				*cLin = l;
				*cCol = c;
				return true;
			} else {
				DEBUG("  DOES NOT CHECK (%d, %d) = %c!\n", l, c, piece);
			}
		}

		DEBUG("  DOES NOT CHECK!\n");
		return false;
	}

	bool isKnightChecking(int lin, int col, int *cLin, int *cCol) const {
		DEBUG("NIGHT behavior\n");

		int dLin[] = { 1,  2,  2,  1, -1, -2, -2, -1 };
		int dCol[] = {-2, -1,  1,  2,  2,  1, -1, -2 };

		char king = m_Pieces[lin][col];
		char expected = king == 'K' ? 'n' : 'N';

		for (int kk = 0; kk < 8; ++kk) {
			int l = lin + dLin[kk];
			int c = col + dCol[kk];

			if (l >= 0 && l < SIZE && c >= 0 && c < SIZE) {
				char piece = m_Pieces[l][c];
				if (piece == expected) {
					DEBUG("  CHECKS (%d, %d) = %c!\n", l, c, piece);
					*cLin = l;
					*cCol = c;
					return true;
				} else {
					DEBUG("  DOES NOT CHECK (%d, %d) = %c!\n", l, c, piece);
				}
			}
		}

		DEBUG("  DOES NOT CHECK!\n");
		return false;
	}

	bool isBishopChecking(int lin, int col, int *cLin, int *cCol) const {
		char king = m_Pieces[lin][col];
		char expected1, expected2;
		if (king == 'K') {
			expected1 = 'b';
			expected2 = 'q';
		} else {
			expected1 = 'B';
			expected2 = 'Q';
		}

		return isBishopChecking(lin, col, cLin, cCol, expected1, expected2);
	}

	bool isBishopChecking(int lin, int col, int *cLin, int *cCol, char expected1, char expected2) const {
		DEBUG("BISHOP behavior: %c, %c\n", expected1, expected2);

		int dLin[] = {-1, -1,  1,  1 };
		int dCol[] = {-1,  1,  1, -1 };

		for (int kk = 0; kk < 4; ++kk) {
			for (int l = lin + dLin[kk], c = col + dCol[kk]; 
				l >= 0 && l < SIZE && c >= 0 && c < SIZE;
				l += dLin[kk], c += dCol[kk])
			{
				char piece = m_Pieces[l][c];
				if (piece != 0) {
					if (piece == expected1 || piece == expected2) {
						DEBUG("  CHECKS (%d, %d) = %c!\n", l, c, piece);
						*cLin = l;
						*cCol = c;
						return true;
					} else {
						DEBUG("  DOES NOT CHECK - PROTECTED (%d, %d) = %c!\n", l, c, piece);
						break;
					}
				} else {
					DEBUG("  EMPTY (%d, %d) = %c!\n", l, c, piece);
				}
			}
		}

		DEBUG("  DOES NOT CHECK!\n");
		return false;
	}

	bool isRookChecking(int lin, int col, int *cLin, int *cCol) const {
		char king = m_Pieces[lin][col];
		char expected1, expected2;
		if (king == 'K') {
			expected1 = 'r';
			expected2 = 'q';
		} else {
			expected1 = 'R';
			expected2 = 'Q';
		}
		char expected = king == 'K' ? 'r' : 'R';

		return isRookChecking(lin, col, cLin, cCol, expected1, expected2);
	}

	bool isRookChecking(int lin, int col, int *cLin, int *cCol, char expected1, char expected2) const {
		DEBUG("ROOK behavior: %c, %c\n", expected1, expected2);

		int dLin[] = { 0, -1,  0,  1 };
		int dCol[] = {-1,  0,  1,  0 };

		for (int kk = 0; kk < 4; ++kk) {
			for (int l = lin + dLin[kk], c = col + dCol[kk]; 
					l >= 0 && l < SIZE && c >= 0 && c < SIZE;
					l += dLin[kk], c += dCol[kk])
			{
				char piece = m_Pieces[l][c];
				if (piece != 0) {
					if (piece == expected1 || piece == expected2) {
						DEBUG("  CHECKS (%d, %d) = %c!\n", l, c, piece);
						*cLin = l;
						*cCol = c;
						return true;
					} else {
						DEBUG("  DOES NOT CHECK - PROTECTED (%d, %d) = %c!\n", l, c, piece);
						break;
					}
				} else {
					DEBUG("  EMPTY (%d, %d) = %c!\n", l, c, piece);
				}
			}
		}

		DEBUG("  DOES NOT CHECK!\n");
		return false;
	}

	bool isKingChecking(int lin, int col, int *cLin, int *cCol) const {
		DEBUG("KING behavior\n");

		int dLin[] = { 0, -1, -1, -1,  0,  1,  1,  1 };
		int dCol[] = {-1, -1,  0,  1,  1,  1,  0, -1 };

		char king = m_Pieces[lin][col];
		char expected = king == 'K' ? 'k' : 'K';

		for (int kk = 0; kk < 8; ++kk) {
			int l = lin + dLin[kk];
			int c = col + dCol[kk];

			if (l >= 0 && l < SIZE && c >= 0 && c < SIZE) {
				char piece = m_Pieces[l][c];
				Color pColor = GetColor(piece);
				if (piece == expected) {
					*cLin = l;
					*cCol = c;
					DEBUG("  CHECKS!\n");
					return true;
				}
			}
		}
		
		DEBUG("  DOES NOT CHECK!\n");
		return false;
	}

};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	unsigned int t;
	for (t = 1; ; ++t) {
		Board board;
		if (board.readBoard() == false) {
			break;
		}

		Board::Color color;
		int lin, col;
		if (board.checkCheck(&color, &lin, &col)) {
			DEBUG("  Checker: %d, %d\n", lin, col);
			printf("Game #%u: %s king is in check.\n", t, Board::ColorToString(color).c_str());
		}
	}

	return 0;
}

