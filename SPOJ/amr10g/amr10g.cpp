#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t, n, k, lb, hb, minDiff, diff;
	int hs[20000];

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &k);

		for (lb = 0; lb < n; ++lb) {
			scanf("%d", &hs[lb]);
		}

		if (k == 1) {
			minDiff = 0;

		} else {
			sort(hs, hs + n);

			minDiff = hs[n - 1] - hs[0];
			for (lb = 0, hb = lb + k - 1; lb < n - k + 1 && hb < n; ++lb, ++hb) {
				diff = hs[hb] - hs[lb];
				if (diff < minDiff) {
					minDiff = diff;
				}
			}
		}

		printf("%d\n", minDiff);
	}
	
	return 0;
}
