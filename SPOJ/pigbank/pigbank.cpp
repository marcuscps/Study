#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int t, e, f, n, ii, jj;
	int value[500], weight[500];
	int cost[10000];

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &e, &f, &n);
		for (ii = 0; ii < n; ++ii) {
			scanf("%d %d", &value[ii], &weight[ii]);
		}

		f -= e;
		
		cost[0] = 0;
		for (ii = 1; ii <= f; ++ii) {
			cost[ii] = -1;
		}
		
		for (ii = 0; ii < n; ++ii) {
			for (jj = 0; jj <= f; ++jj) {
				if (cost[jj] != -1 && jj + weight[ii] <= f) { 
					if (cost[jj + weight[ii]] == -1 || cost[jj + weight[ii]] > cost[jj] + value[ii]) {
						cost[jj + weight[ii]] = cost[jj] + value[ii];
					}
				}
			}
		}
		
		if (cost[f] == -1) {
			printf("This is impossible.\n");
		} else {
			printf("The minimum amount of money in the piggy-bank is %d.\n", cost[f]);
		}
	}
	
	return 0;
}
