#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

	const int MAX_P = 101;
	const int MAX_W = 501;

    int b, n, ii, iil1, jj;
    int w[MAX_P], v[MAX_P];
    
    int m0i[MAX_W], m1i[MAX_W];
    int *m0, *m1;

	while (scanf("%d %d", &b, &n) == 2) {
        if (b == 0 && n == 0) {
			break;
		}
      
		for (ii = 0; ii < n; ++ii) {
			scanf("%d %d", &w[ii], &v[ii]);
		}

        m0 = m0i;
        m1 = m1i;

		for (jj = 0; jj <= b; ++jj) {
			m0[jj] = 0;
		}

		for (ii = 1; ii <= n; ++ii) {
			iil1 = ii - 1;
			for (jj = 0; jj <= b; ++jj) {
				if (w[iil1] <= jj) {
					m1[jj] = max(m0[jj], m0[jj - w[iil1]] + v[iil1]);
				} else {
					m1[jj] = m0[jj];
				}
			}
            swap(m0, m1);
		}
 
		while (b > 0 && m0[b - 1] == m0[b]) {
			--b;
		}

		printf("%d %d\n", b, m0[b]);
    }
	
	return 0;
}
