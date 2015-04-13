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

struct Schweisen {
	int y;
	int q;

	Schweisen() : y(-1), q(0) { }

	Schweisen(int y, int q) : y(y), q(q) { }

	bool operator<(const Schweisen &other) {
		return y < other.y;
	}
};

typedef map<int, Schweisen> SMap;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int x, y, p, q;
	char c;
	int cx, cy, cn, cz, cw;
	while (1) {
		cin >> x >> y >> p;
		if (x == 0 && y == 0 && p == 0) break;

		SMap field[x];
		cin >> q;
		while (q--) {
			cin >> c;
			if (c == 'A') {
				cin >> cn >> cx >> cy;
				ODEBUG("I found " << cn << " schweisen at (" << cx << ", " << cy << ")" << endl);
				SMap &column = field[cx];
				auto it = column.find(cy);
				if (it != column.end()) {
					(it->second).q += cn;
				} else {
					column[cy] = Schweisen(cy, cn);
				}
				continue;
			}

			if (c == 'P') {
				cin >> cx >> cy >> cz >> cw;
				ODEBUG("How much money do I need to kill every schweisen inside (" << cx << ", " << cy << ") to (" << cz << ", " << cw << ")?" << endl);
				int sum = 0;
				int beginx = min(cx, cz);
				int endx   = max(cx, cz);
				int beginy = min(cy, cw);
				int endy   = max(cy, cw);
				for (int ii = beginx; ii <= endx; ++ii) {
					SMap &column = field[ii];
					auto it1 = column.lower_bound(beginy);
					auto it2 = column.lower_bound(endy + 1);
					for (; it1 != it2; ++it1) {
						sum += (it1->second).q;
						ODEBUG("    Adding (" << ii << ", " << (it1->second).y << ") --> " << (it1->second).q << "  -  SUM = " << sum << endl);
					}
				}
				cout << (sum * p) << endl;
				continue;
			}
			
			ODEBUG("Invalid command: " << c << ". Ignoring..." << endl);
		}
		cout << endl;
	}

    return 0;
}

