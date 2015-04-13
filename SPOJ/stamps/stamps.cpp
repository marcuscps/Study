#include <cstdio>
#include <iostream>

using namespace std;

inline void insertionSort(int *c, int pos) {
	unsigned int val = c[pos];
	for (; pos > 0 && c[pos - 1] > val; --pos) {
		c[pos] = c[pos - 1];
	}
	c[pos] = val;
}

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t, t0;
	int s;
	int f;
	int fs[1001];
	int rf;
	int ii;

	scanf("%d", &t0);
	for (t = 1; t <= t0; ++t) {
		scanf("%d %d", &s, &f);
		rf = 0;

		for (ii = 0; ii < f; ++ii) {
			scanf("%d", &fs[ii]);
		}

		for (ii = 1; ii < f; ++ii) {
			insertionSort(fs, ii);
		}

		for (ii = f - 1; ii >= 0 && s > 0; --ii) {
			s -= fs[ii];
			++rf;
		}

		printf("Scenario #%d:\n", t);
		if (s > 0) {
			printf("impossible\n\n");
		} else {
			printf("%d\n\n", rf);
		}
	}

	return 0;
}

