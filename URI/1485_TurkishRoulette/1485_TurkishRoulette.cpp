#include <iostream>
#include <cstdio>
#include <limits>

using namespace std;

int s, b;
int vs[250];
int	profit[125][250];

#define Position(pos)	(((pos) >= s) ? ((pos) - s) : (pos))

#if 0  // Easy to understand
inline int place(int b0) {
	int maxProfit[126][250];

	int b1 = b - 1;
	int bb = b1;
	do {
		int first = (bb << 1);
		int last  = ((s - 2) - ((b1 - bb) << 1));

		int best = numeric_limits<int>::min();
		for (int ii = last; ii >= first; --ii) {
			int p1 = Position(b0 + ii);
			int v = profit[bb][p1];
			
			if (bb != b1) {
				int p2 = Position(p1 + 2);
				v += maxProfit[bb + 1][p2];
			}

			if (v > best) {
				best = v;
			}
			maxProfit[bb][p1] = best;
		}
	} while (--bb > 0);

	if (b > 1) {
		maxProfit[0][b0] = profit[0][b0] + maxProfit[1][Position(b0 + 2)];
	}

	return maxProfit[0][b0];
}

#else // Optimized
inline int place(int b0) {
	int maxProfit[250] = { 0 };

	int first = ((b - 1) << 1);
	int last  = (s - 2);
	int n = last - first;
	int v;

	for (int bb = b - 1; bb > 0; --bb) {
		int best = numeric_limits<int>::min();
		for (int ii = last, kk = n; ii >= first; --ii, --kk) {
			v = maxProfit[kk] + profit[bb][Position(b0 + ii)];
			if (v > best) {
				best = v;
			}
			maxProfit[kk] = best;
		}
		first -= 2;
		last -= 2;
	}

	return maxProfit[0] += profit[0][b0];
}
#endif

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	while (true) {
		cin >> s >> b;
		if (s == 0 && b == 0) break;

		// Read slots
		for (int ss = 0; ss < s; ++ss) cin >> vs[ss];

		// Read balls
		// Filling profit[bb][ss] = (-1) * Ball[bb] * (Slot[ss] + Slot[ss + 1]
		int v0 = vs[0];
		int ball;
		for (int bb = 0; bb < b; ++bb) {
			cin >> ball;
			ball = -ball;
			for (int ss = 0; ss < s - 1; ++ss) {
				profit[bb][ss] = ball * (vs[ss] + vs[ss + 1]);
			}
			profit[bb][s - 1] = ball * (vs[s - 1] + v0);
		}

		int best = std::numeric_limits<int>::min();
		for (int ii = 0; ii < s; ++ii) {
			int v = place(ii);
			if (v > best) best = v;
		}

		cout << best << endl;
	}

    return 0;
}
