#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int t, h, w;
	int ii, iip1, jj, val;
	int v[100][100];
	int r[100][100];
    int *vp, *rp, *rp1p;

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &h, &w);
		for (ii = 0; ii < h; ++ii) {
			for (jj = 0; jj < w; ++jj) {
				scanf("%d", &v[ii][jj]);
			}
		}

        rp = r[0];
        vp = v[0];
		for (jj = 0; jj < w; ++jj) {
			rp[jj] = vp[jj];
		}
		--h;
        --w;
		for (ii = 0; ii < h; ++ii) {
            rp = r[ii];
            rp1p = r[ii + 1];
            vp = v[ii + 1];
            
            rp1p[0] = vp[0] + max(rp[0], rp[1]);
			for (jj = 1; jj < w; ++jj) {
                rp1p[jj] = vp[jj] + max(rp[jj - 1], max(rp[jj], rp[jj + 1]));
			}
            rp1p[w] = vp[w] + max(rp[w - 1], rp[w]);
		}
        
		val = -1;
        rp = r[h];
		for (jj = 0; jj <= w; ++jj) {
			if (rp[jj] > val) {
				val = rp[jj];
			}
		}
		printf("%d\n", val);
	}
	
	return 0;
}
