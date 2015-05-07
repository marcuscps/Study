#include <iostream>
#include <cstdio>
#include <iomanip>
#include <map>
#include <cstring>

using namespace std;

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

#define MAX_VALUES 100002

int read(int *freqTree, int index) {
   int count = 0;
   while (index > 0) {
      count += freqTree[index];
      index -= (index & -index);
   }
   return count;
}

void update(int *freqTree, size_t index, int delta) {
   while (index < MAX_VALUES) {
      freqTree[index] += delta;  
      index += (index & -index);
   }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int values[MAX_VALUES];
	int zeros[MAX_VALUES];
	int negs[MAX_VALUES];

	int n, k;

	while (cin >> n >> k) {
		memset(zeros, 0, n * sizeof(int));
		memset(negs, 0, n * sizeof(int));

		ODEBUG("N: " << n << "  -  K: " << k << endl);
		for (int ii = 1; ii <= n; ++ii) {
			cin >> values[ii];
			ODEBUG("V = " << values[ii] << endl);
			if (values[ii] == 0) {
				update(zeros, ii, 1);
			} else if (values[ii] < 0) {
				update(negs, ii, 1);
			}
		}

		while (k--) {
			char c;
			cin >> c;
			if (c == 'C') {
				int i, v;
				cin >> i >> v;
				if (v > 0) {
					if (values[i] == 0) {
						update(zeros, i, -1);
					}
					if (values[i] < 0) {
						update(negs, i, -1);
					}
				} else if (v == 0) {
					if (values[i] != 0) {
						update(zeros, i, 1);
					}
					if (values[i] < 0) {
						update(negs, i, -1);
					}
				} else {
					if (values[i] == 0) {
						update(zeros, i, -1);
					}
					if (values[i] >= 0) {
						update(negs, i, 1);
					}
				}

				values[i] = v;
			} else if (c == 'P') {
				int i, j;
				cin >> i >> j;
				--i;
				int nz = read(zeros, j) - read(zeros, i);
				if (nz > 0) {
					cout << "0";
				} else {
					int nn = read(negs, j) - read(negs, i);
					cout << ((nn & 1) ? "-" : "+");
				}
			}
		}
		cout << endl;
	}

    return 0;
}

