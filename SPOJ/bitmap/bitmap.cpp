#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

struct Dot {
	int i;
	int j;
	int v;

	Dot() { }

	Dot(int i, int j, int v) : i(i), j(j), v(v) { }
};


typedef queue<Dot> DotQueue;


//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	int n, m;
	char c;
	int d[183][183];
	int ii, jj, delta;
	DotQueue visits;
	int maxd;
	int dII[] = { -1,  1,  0,  0 };
	int dJJ[] = {  0,  0, -1,  1 };
	int val;
	Dot dot;

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d\n", &n, &m);
		maxd = n * m;
		for (ii = 0; ii < n; ++ii) {
			for (jj = 0; jj < m; ++jj) {
				scanf("%c", &c);
				if (c == '1') {
					d[ii][jj] = 0;
					visits.push(Dot(ii, jj, 0));
				} else {
					d[ii][jj] = maxd;
				}
			}
			scanf("\n");
		}


		while (visits.empty() == false) {
			dot = visits.front();
			visits.pop();

			for (delta = 0; delta < 4; ++delta) {
				ii = dot.i + dII[delta];
				jj = dot.j + dJJ[delta];
				val = dot.v + 1;

				if (ii >= 0 && ii < n && jj >= 0 && jj < m && d[ii][jj] > val) {
					d[ii][jj] = val;
					visits.push(Dot(ii, jj, val));
				}
			}
		}

		for (ii = 0; ii < n; ++ii) {
			for (jj = 0; jj < m; ++jj) {
				printf("%d", d[ii][jj]);
				if (jj + 1 != m) {
					printf(" ");
				}
			}
			printf("\n");
		}
	}

	return 0;
}

