#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...) printf( __VA_ARGS__ )
	const char cValues[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
	const char suits[] = { 'd', 's', 'h', 'c' };
#else
	#define DEBUG(...)
#endif

//================================================================================================
struct Card {
	int  val;
	int suit;

	Card() {
		val = 0;
		suit = 0;
	}

	Card(char c1, char c2) {
		if (c1 >= '2' && c1 <= '9') {
			val = c1 - '2';
		} else switch (c1) {
			case 'T': val = 8; break;
			case 'J': val = 9; break;
			case 'Q': val = 10; break;
			case 'K': val = 11; break;
			case 'A': val = 12; break;
		}

		switch (c2) {
			case 'D': suit = 0; break;
			case 'S': suit = 1; break;
			case 'H': suit = 2; break;
			case 'C': suit = 3; break;
		}
	}
};

//================================================================================================
void insertionSort(Card **cards, int length) {
	for (int ii = 1; ii < length; ++ii) {
		Card *x = cards[ii];
		int jj = ii;
		while (jj > 0 && cards[jj - 1]->val > x->val) {
			cards[jj] = cards[jj - 1];
			--jj;
		}
		cards[jj] = x;
	}
}

//================================================================================================
void countCards(Card **cards, int *values, int *suits) {
	for (int ii = 0; ii < 5; ++ii) {
		++values[cards[ii]->val];
		++suits[cards[ii]->suit];
	}
}

//================================================================================================
// 2000008000 + (0 ~ 12):   Straight Flush
// 2000007000 + (0 ~ 12):   Four of a kind
// 2000006000 + (0 ~ 12):   Full house
// 2000005000 + (0 ~ 12):   Flush
// 2000004000 + (0 ~ 12):   Straight
// 2000003000 + (0 ~ 12):   Three of a kind
// 2000002000 + (0 ~ 12):   2 Pairs
// 2000001000 + (0 ~ 12):   1 pair
//        0 ~ 1211100907:   Hi Card (12, 11, 10, 09, 07).
int detectGame(Card **cards, int *values, int *suits) {
	const int DELTA_S_FLUSH  = 2000008000;
	const int DELTA_4_KIND   = 2000007000;
	const int DELTA_F_HOUSE  = 2000006000;
	const int DELTA_FLUSH    = 2000005000;
	const int DELTA_STRAIGHT = 2000004000;
	const int DELTA_3_KIND   = 2000003000;
	const int DELTA_2_PAIRS  = 2000002000;
	const int DELTA_1_PAIR   = 2000001000;

	// Detecting flush
	int flushH = -1;
	for (int ii = 0; ii < 4 && flushH == -1; ++ii) {
		if (suits[ii] == 5) {
			for (int jj = 12; jj > 0; --jj) {
				if (values[jj] != 0) {
					flushH = jj;
					break;
				}
			}
		}
	}

	// Detecting straight
	int straightH = -1;
	int straightB = 0;
	for (straightB = 0; straightB < 13; ++straightB) {
		if (values[straightB] != 0) break;
	}
	if (straightB <= 8) {
		straightH = straightB + 4;
		for (int ii = 1; ii < 5; ++ii) {
			if (values[straightB + ii] == 0) {
				straightH = -1;
				break;
			}
		}
	}
	
	if (flushH != -1 && straightH != -1) {
		DEBUG("STRAIGHT FLUSH: %c\n", cValues[straightH]);
		return DELTA_S_FLUSH + straightH;
	}

	// Detecting four of a kind and pairs
	for (int ii = 12; ii >= 0; --ii) {
		if (values[ii] == 4) {
			DEBUG("FOAK: %c\n", cValues[ii]);
			return DELTA_4_KIND + ii;
		}
	}

	// Detecting three of a kind and pairs
	int toakV = -1;
	int pairs = 0;
	int hPair = 0;
	for (int ii = 12; ii >= 0; --ii) {
		if (values[ii] == 3) {
			toakV = ii;
		} else if (values[ii] == 2) {
			if (ii > hPair) hPair = ii;
			++pairs;
			DEBUG("PAIR %c - ", cValues[ii]);
			if ((pairs == 2 || toakV >= 0)) break;
		}
	}

	if (toakV != -1 && pairs > 0) {
		DEBUG("FULL HOUSE: %c\n", cValues[toakV]);
		return DELTA_F_HOUSE + toakV;
	} else if (flushH != -1) {
		DEBUG("FLUSH: %c\n", cValues[flushH]);
		return DELTA_FLUSH + flushH;
	} else if (straightH != -1) {
		DEBUG("STRAING: %c\n", cValues[straightH]);
		return DELTA_STRAIGHT + straightH;
	} else if (toakV != -1) {
		DEBUG("TOAK: %c\n", cValues[toakV]);
		return DELTA_3_KIND + toakV;
	} else if (pairs == 2) {
		DEBUG("2 PAIRS: %c\n", cValues[hPair]);
		return DELTA_2_PAIRS + hPair;
	} else if (pairs == 1) {
		DEBUG("PAIR: %c\n", cValues[hPair]);
		return DELTA_1_PAIR + hPair;
	}

	long long int hCard = 0;
	for (int ii = 12; ii >= 0; --ii) {
		if (values[ii] != 0) {
			hCard = (hCard * 100) + ii;
		}
	}

	DEBUG("HI CARD: %d\n", hCard);
	return hCard;
}

//================================================================================================
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	Card *cards[10];
	Card **bCards = cards;
	Card **wCards = cards + 5;

	char c1, c2;
	int ii;
	int bScore, wScore;
#ifdef DEBUG_ON
	int t = 1;
#endif

	while (1) {
		int bValues[13] = { 0 };
		int wValues[13] = { 0 };
		int bSuits[4] = { 0 };
		int wSuits[4] = { 0 };

		for (ii = 0; ii < 10; ++ii) {
			if (scanf(" %c%c", &c1, &c2) != 2) {
				return 0;
			}
			cards[ii] = new Card(c1, c2);
		}
		scanf("\n");

		DEBUG("\nB's: "); for (ii = 0; ii < 5; ++ii)  { DEBUG("%c%c ", cValues[bCards[ii]->val], suits[bCards[ii]->suit]); }
		DEBUG("\nW's: "); for (ii = 0; ii < 5; ++ii)  { DEBUG("%c%c ", cValues[wCards[ii]->val], suits[wCards[ii]->suit]); }

		DEBUG("\nSorting...\n");
		insertionSort(bCards, 5);
		insertionSort(wCards, 5);

		DEBUG("Counting...\n");
		countCards(bCards, bValues, bSuits);
		countCards(wCards, wValues, wSuits);


		DEBUG("\nB's: "); for (ii = 0; ii < 5; ++ii)  { DEBUG("%c%c ", cValues[bCards[ii]->val], suits[bCards[ii]->suit]); }
		DEBUG("\n#s:  "); for (ii = 0; ii < 13; ++ii) { DEBUG("%02d ", bValues[ii]); }
		DEBUG("\nSs:  "); for (ii = 0; ii < 4; ++ii)  { DEBUG("%02d ", bSuits[ii]); }
		DEBUG("\nW's: "); for (ii = 0; ii < 5; ++ii)  { DEBUG("%c%c ", cValues[wCards[ii]->val], suits[wCards[ii]->suit]); }
		DEBUG("\n#s:  "); for (ii = 0; ii < 13; ++ii) { DEBUG("%02d ", wValues[ii]); }
		DEBUG("\nSs:  "); for (ii = 0; ii < 4; ++ii)  { DEBUG("%02d ", wSuits[ii]); }


		DEBUG("\nBlack Score: ");
		bScore = detectGame(bCards, bValues, bSuits);
		DEBUG("White Score: ");
		wScore = detectGame(wCards, wValues, wSuits);

		DEBUG("TEST %d --> ", t++);
		if (bScore == wScore) {
			printf("Tie.\n");
		} else if (bScore > wScore) {
			printf("Black wins.\n");
		} else {
			printf("White wins.\n");
		}

		for (ii = 0; ii < 10; ++ii) {
			delete cards[ii];
		}
	}

	return 0;
}
