#include <iostream>
#include <cstdio>

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;


class Graph {
public:
	static const int MAXV		= 100;
	static const int MAXDEGREE	= 50;

	int edges[MAXV+1][MAXDEGREE];
	int degree[MAXV+1];
	int nvertices;
	int nedges;

	bool discovered[MAXV];	// which vertices have been found
	bool color[MAXV];		// vertex colors

public:

	void read(bool directed, int v) {
		int m;
		int x, y;

		initializeGraph();

		nvertices = v;
		DEBUG("nvertices = %d\n", nvertices);

		scanf("%d", &m);
		DEBUG("edge count = %d\n", m);
		for (int ii = 0; ii < m; ++ii) {
			scanf("%d %d", &x, &y);
			insertEdge(x, y, directed);
		}
	}

	void initializeGraph() {
		nvertices = 0;
		nedges = 0;
		for (int ii = 0; ii < MAXV; ++ii) {
			degree[ii] = 0;
		}
	}

	void insertEdge(int x, int y, bool directed) {
		if (degree[x] > MAXDEGREE) {
			printf("Warning: insertion(%d, %d) exceeds max degree\n", x, y);
		}

		edges[x][degree[x]] = y;
		++degree[x];
		DEBUG("Edge: %d -> %d    Degree: %d\n", x, y, degree[x]);

		if (directed == false) {
			insertEdge(y, x, true);
		} else {
			++nedges;
		}
	}

	bool tryBicolor(int v) {
		initializeSearch();

		color[v] = true;

		return tryBicolorInternal(v);
	}

private:
	bool tryBicolorInternal(int v) {
		// This is a DFS, with color checking
		
		discovered[v] = true;
		DEBUG("Discovered: %d - Color: %d\n", v, color[v]);

		for (int ii = 0; ii < degree[v]; ++ii) {
			int y = edges[v][ii];
			if (discovered[y] == false) {
				color[y] = !color[v];

				if (tryBicolorInternal(y) == false) {
					return false;
				}
			} else if (color[y] == color[v]) {
				DEBUG("Colors DO conflict: color[%d] == color[%d]  (%d)\n", y, v, color[v]);
				return false;
			} else {
				DEBUG("Colors DO NOT conflict: color[%d] != color[%d]  (%d != %d)\n", y, v, color[y], color[v]);
			}
		}

		return true;
	}

	void initializeSearch() {
		for (int ii = 0; ii < nvertices; ++ii) {
			discovered[ii] = false;
		}
	}

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	while (true) {
		// Desired numerator and denominator
		int n;
		scanf("%d", &n);
		if (n == 0) break;

		Graph g;
		g.read(false, n);

		if (g.tryBicolor(0) == false) {
			printf("NOT ");
		}
		printf("BICOLORABLE.\n");
	}

    return 0;
}
