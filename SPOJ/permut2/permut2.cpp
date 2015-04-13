#include <cstdio>
#include <iostream>

using namespace std;

typedef unsigned int uint;


inline void testP(uint *p, uint n) {
	for (uint ii = 0; ii < n; ++ii) {
		if (p[p[ii] - 1] != ii + 1) {
			printf("not ambiguous\n");
			return;
		}
	}
	printf("ambiguous\n");
}

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	uint n;
	uint p[100001];

	while (1) {
		scanf("%u", &n);
		if (n == 0) break;
		for (uint ii = 0; ii < n; ++ii) {
			scanf("%u", &p[ii]);
		}
		testP(p, n);
	}

	return 0;
}

