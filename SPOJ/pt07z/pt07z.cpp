#include <cstdio>
#include <iostream>

using namespace std;

int n, m[10001][10001];
//#define DEBUG(fmt, ...) printf(fmt, __VA_ARGS__)
#define DEBUG(fmt, ...)

//=================================================================================================
int dfs(int node) {
	DEBUG("  Visiting node %d\n", node);
	m[node][0] = 1;
	int lp = 0, p;
	for (int ii = 1; ii <= n; ++ii) {
		if (m[node][ii] != 0) {
			if (m[ii][0] == 0) {
				p = 1 + dfs(ii);
				if (p > lp) lp = p;
			} else {
				DEBUG("    Node %d already visited.\n", ii);
			}
		} else {
			DEBUG("    No path to node %d\n", ii);
		}
	}
	m[node][0] = 0;
	return lp;
}

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int u, v, ii, jj, lp, p;

	scanf("%d", &n);
	DEBUG("N = %d\n", n);
	for (ii = 0; ii <= n; ++ii) {
		for (jj = 0; jj <= n; ++jj) {
			m[ii][jj] = 0;
		}
	}

	for (ii = 1; ii < n; ++ii) {
		scanf("%d %d", &u, &v);
		DEBUG("Node %d <--> %d\n", u, v);
		m[u][v] = 1;
		m[v][u] = 1;
		++m[0][u];
		++m[0][v];
	}

	lp = 0;
	for (ii = 1; ii <= n; ++ii) {
		if (m[0][ii] == 1) {
			DEBUG("Starting at node %d\n", ii);
			p = dfs(ii);
			if (p > lp) lp = p;
			if (lp == n - 1) break;
		}
	}
	printf("%d\n", lp);


	return 0;
}

