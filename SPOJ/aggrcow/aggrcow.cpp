#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n, c;

bool tryIt(int *a, int dist) {
	int cows = 1, pivot = a[0];
	for (int next = 1; next < n; ++next) {
		if (a[next] - pivot >= dist) {
			if (++cows >= c) {
				// printf(". Got it!\n");
				return true;
			}
			pivot = a[next];
			// printf(", %d", cows);
		}
	}
	// printf(". FAILED!\n");
	return false;
}

int bs(int *a) {
	if (n == 2) {
		return a[n - 1];
	}

	int min = 0, max = a[n - 1], mid = 0, ok = -1;
	while (min < max) {
		mid = (min + max) / 2;
		//printf("Trying %d (min = %d, max = %d): 1", mid, min, max);
		if (tryIt(a, mid)) {
			ok = mid;
			min = mid + 1;
		} else {
			max = mid;
		}
	}
	return ok;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	scanf("%d\n", &t);
	while (t--) {
		scanf("%d %d", &n, &c);
		
		int a[n];
		for (int ii = 0; ii < n; ++ii) {
			scanf("%d", &a[ii]);
		}

		sort(a, a + n);

		printf("%d\n", bs(a));
	}
}
