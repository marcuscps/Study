#include <iostream>
#include <cstdio>
#include <map>

#ifndef ONLINE_JUDGE
	#define DEBUG_ON
#endif
#ifdef DEBUG_ON
	#define DEBUG_ST(x)		x
	#define DEBUG(...)		printf("## " __VA_ARGS__)
	#define ODEBUG(...)		std::cout << "## " << __VA_ARGS__
	#define MDEBUG(...)		printf(__VA_ARGS__)
	#define OMDEBUG(...)	std::cout << __VA_ARGS__
#else
	#define DEBUG_ST(x)
	#define DEBUG(...)
	#define ODEBUG(...)
	#define MDEBUG(...)
	#define OMDEBUG(...)
#endif

using namespace std;

typedef map<int, int> SuitMap;

struct Suit {
	SuitMap cards;

	Suit() {
	}

	void add(int card) {
		SuitMap::iterator it = cards.find(card);
		if (it == cards.end()) {
			cards[card] = 1;
		} else {
			++it->second;
		}
	}

	SuitMap::iterator getHighest() {
		SuitMap::reverse_iterator it = cards.rbegin();
		if (it != cards.rend()) {
			return --(it.base());
		}
		return cards.end();
	}

	void remove(SuitMap::iterator it) {
		--it->second;
		if (it->second == 0) {
			cards.erase(it);
		}
	}

	SuitMap::iterator getCard(int value) {
		OMDEBUG("[ ");
		for (auto it = cards.begin(); it != cards.end(); ++it) {
			OMDEBUG(it->first << " ");
		}
		OMDEBUG("]");
		auto it = cards.find(value);
		if (it != cards.end()) {
			OMDEBUG(value << "-> " << it->first);
		} else {
			OMDEBUG(value << "X ");
		}
		return it;
	}

	void clear() {
		cards.clear();
	}

	inline SuitMap::iterator end() {
		return cards.end();
	}
	
	static int getIndex(char suit) {
		switch (suit) {
		case 'S': return 0;
		case 'H': return 1;
		case 'D': return 2;
		default:  return 3;
		}
	}

};

struct Player {
	int id;
	Suit suits[4];
	int total;

	Player() {
		total = 0;
	}

	void setId(int id) {
		this->id = id;
	}

	void reset() {
		ODEBUG("Resetting player " << id << endl);
		total = 0;
		for (int ii = 0; ii < 4; ++ii) {
			suits[ii].clear();
		}
	}

	void addCard(int num, int suit) {
		ODEBUG("  Player " << id << " add card: " << num << " " << suit << endl);
		suits[suit].add(num);
		++total;
	}

	bool getCard(int &num, int &suit) {
		ODEBUG("  Player " << id << " Getting card: " << num << " " << suit << ": ");

		int bestC = -1;
		int bestS = -1;
		SuitMap::iterator bestIt = suits[suit].end();

		SuitMap::iterator it = suits[suit].getHighest();
		if (it != suits[suit].end()) {
			bestC = it->first;
			bestS = suit;
			OMDEBUG("(" << bestC << " - " << bestS << ") ");
			bestIt = it;
		}

		for (int ii = 0; ii < 4; ++ii) {
			if (ii != suit) {
				OMDEBUG("F" << ii << " ");
				SuitMap::iterator it = suits[ii].getCard(num);
				if (it != suits[ii].end()) {
					if ((it->first > bestC) || (it->first == bestC && ii < bestS)) {
						bestC = it->first;
						bestS = ii;
						OMDEBUG("(" << bestC << " - " << bestS << ") ");
						bestIt = it;
					} else {
						OMDEBUG("IG(" << it->first << " - " << it->second << ") ");
					}
				}
			} else {
				OMDEBUG("I" << ii << " ");
			}
		}

		if (bestC != -1) {
			suits[bestS].remove(bestIt);
			num = bestC;
			suit = bestS;
			--total;
			OMDEBUG("FOUND " << num << " - " << suit << endl);
			return true;
		}

		OMDEBUG("NO CARDS!" << endl);
		return false;
	}

};

void cardAction(int num, int suit, bool &dir, int &draws, bool &skip) {
	ODEBUG("  --> CARD: " << num << " " << suit << " - ACTION: ");
	switch (num) {
		case 12:
			OMDEBUG("Q - Invert." << endl);
			dir = !dir;
			break;
		case 7:
			OMDEBUG("7 - Next draw 2 cards and skip." << endl);
			draws = 2;
			skip = true;
			break;
		case 1:
			OMDEBUG("A - Next draw 1 cards and skip." << endl);
			draws = 1;
			skip = true;
			break;
		case 11:
			OMDEBUG("J - Skip." << endl);
			skip = true;
			break;
		default:
			OMDEBUG("NONE." << endl);
	}
}

void drawCard(int &num, int &suitIndex) {
	char suit;
	scanf("%d %c", &num, &suit);
	suitIndex = Suit::getIndex(suit);
	ODEBUG("  draw card: " << num << " " << suit << "(" << suitIndex << ")" << endl);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int p, m, n;
	char suit;
	int num, suitIndex;
	Player *player;
	Player players[10];
	
	for (int ii = 0; ii < 10; ++ii) {
		players[ii].setId(ii + 1);
	}

	while (true) {
		scanf("%d %d %d", &p, &m, &n);
		if (p == 0 && m == 0 && n == 0) break;

		ODEBUG("New game: P = " << p << "  -  M = " << m << "  -  N = " << n << endl);

		ODEBUG("Initial hands:" << endl);
		for (int pp = 0; pp < p; ++pp) {
			player = &players[pp];
			for (int mm = 0; mm < m; ++mm) {
				drawCard(num, suitIndex);
				player->addCard(num, suitIndex);
			}
			n -= m;
		}

		ODEBUG("PLAY:" << endl);

		int cur = 0;
		player = &players[cur];

		bool dir  = true;
		int draws = 0;
		bool skip = false;

		scanf("%d %c", &num, &suit);
		suitIndex = Suit::getIndex(suit);
		cardAction(num, suitIndex, dir, draws, skip);
		--n;

		while (draws > 0) {
			if (n--) {
				int numn, indexn;
				drawCard(numn, indexn);
				player->addCard(numn, indexn);
			}
			--draws;
		}

		while (true) {
			// Winner
			if (player->total == 0) {
				ODEBUG("Player is a winner! " << player->id << endl);
				printf("%d\n", player->id);
				break;
			}

			if (skip) {
				ODEBUG("  Player " << player->id << " skipped!" << endl);
				skip = false;
			} else {
				if (player->getCard(num, suitIndex)) {
					cardAction(num, suitIndex, dir, draws, skip);
				} else {
					ODEBUG("  Player " << player->id << " has no suitable card." << endl);
					if (n--) {	
						int numn, indexn;
						drawCard(numn, indexn);
						if (numn == num || indexn == suitIndex) {
							ODEBUG("  suitable card." << endl);
							num = numn;
							suitIndex = indexn;
							cardAction(num, suitIndex, dir, draws, skip);
						} else {
							player->addCard(numn, indexn);
						}
					}
				}
			}

			// Winner
			if (player->total == 0) {
				ODEBUG("Player is a winner! " << player->id << endl);
				printf("%d\n", player->id);
				break;
			}

			if (dir) {
				ODEBUG("  Next " << player->id << " --> ");
				++cur;
				if (cur >= p) cur = 0;
			} else {
				ODEBUG("  Next " << player->id << " <-- ");
				--cur;
				if (cur < 0) cur = p - 1;
			}
			player = &players[cur];
			OMDEBUG(player->id << endl);

			while (draws > 0) {
				if (n--) {
					int numn, indexn;
					drawCard(numn, indexn);
					player->addCard(numn, indexn);
				}
				--draws;
			}
		}

		ODEBUG("Remaining cards in the stock:" << endl);
		while (n > 0) {
			scanf("%d %c", &num, &suit);
			ODEBUG("  card: " << num << " " << suit << endl);
			--n;
		}

		for (int ii = 0; ii < p; ++ii) {
			players[ii].reset();
		}

	}

    return 0;
}

