#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

struct Number {
	char n[4];

	Number() {
		n[0] = n[1] = n[2] = n[3] = 0;
	}

	Number(int v) {
		n[0] = v % 10;	v /= 10;
		n[1] = v % 10;	v /= 10;
		n[2] = v % 10;	v /= 10;
		n[3] = v % 10;
	}

	void read() {
		for (int ii = 3; ii >= 0; --ii) {
			int v;
			scanf("%d", &v);
			n[ii] = (char)v;
		}
	}

	int getValue() {
		return (n[3] * 1000) + (n[2] * 100) + (n[1] * 10) + n[0];
	}

	void getNextNumbers(vector<int> &result) {
	    for (int ii = 3; ii >= 0; --ii) {
			short int b = n[ii];
			n[ii] = (n[ii] + 1) % 10;
			result.push_back(getValue());
			n[ii] = b;
			--n[ii];
			if (n[ii] == -1) n[ii] = 9;
			result.push_back(getValue());
			n[ii] = b;
		}
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t;
	scanf("%d", &t);
	while (t--) {
		vector<int> distance;
		vector<bool> visited;
		queue<int> q;

#ifdef PRINT_PATH
		vector<int> parent;
		parent.reserve(10000);
#endif

		distance.reserve(10000);
		visited.reserve(10000);
		for (int ii = 0; ii < 10000; ++ii) {
			visited[ii] = false;
		}

		Number initialN;
		initialN.read();
		int initial = initialN.getValue();
		DEBUG("Initial number: %d\n", initial);

		Number targetN;
		targetN.read();
		int target = targetN.getValue();
		DEBUG("Target number: %d\n", target);

		int k;
		scanf("%d", &k);
		for (int ii = 0; ii < k; ++ii) {
			Number constraintN;
			constraintN.read();
			int constraint = constraintN.getValue();
			DEBUG("Constraint: %d\n", constraint);
			visited[constraint] = true;
		}

		distance[initial] = 0;
		q.push(initial);
		bool found = false;
		while (q.empty() == false) {
			int v = q.front();
			q.pop();

			if (visited[v]) continue;
			visited[v] = true;

			DEBUG("TRYING %d ... DISTANCE: %d\n", v, distance[v]);
			if (v == target) {
				found = true;
				break;
			}

			vector<int> nexts;
			Number vn(v);
			vn.getNextNumbers(nexts);

			for (vector<int>::iterator ii = nexts.begin(); ii != nexts.end(); ++ii) {
				if (visited[*ii]) continue;
				distance[*ii] = distance[v] + 1;
#ifdef PRINT_PATH
				parent[*ii] = v;
#endif
				q.push(*ii);
			}
		}

		printf("%d\n", found ? distance[target] : -1);
#ifdef PRINT_PATH // Print the path
		if (found == true) {
			int v = target;
			while (v != initial) {
				printf("%d <-- ", v);
				v = parent[v];
			}
			printf("%d\n", initial);
		}
#endif
	}

    return 0;
}
