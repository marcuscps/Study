#include <cstdio>

using namespace std;

int main() {
	int t, n, p, e;
	while (true) {
		scanf("%d %d\n", &t, &n);
		if (t == 0) break;

		// e = (3 * n) - sum(points)
		e = 3 * n;
		for (int ii = 0; ii < t; ++ii) {
			scanf("%*s %d", &p);
			e -= p;
		}

		printf("%d\n", e);
	}

    return 0;
}

