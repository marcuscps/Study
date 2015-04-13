#include <iostream>
#include <cstdio>

using namespace std;

typedef unsigned long long int ullint;
typedef unsigned long int ulint;

ullint mergeAndCount(ullint *v, ulint start, ulint mid, ulint end, ullint *temp) {
    ulint aii = start;
	ulint bii = mid;
	ulint tii = 0;
	ullint invs = 0;
	
	while (aii < mid && bii < end) {
		if (v[aii] <= v[bii]) {
			temp[tii++] = v[aii++];
		} else {
			temp[tii++] = v[bii++];
			invs += (mid - aii);
		}
	}
	while (aii < mid) {
		temp[tii++] = v[aii++];
	}
	while (bii < end) {
		temp[tii++] = v[bii++];
	}
	for (aii = 0; aii < tii; ++aii) {
		v[start++] = temp[aii];
	}

	return invs;
}

ullint sortAndCount(ullint *v, ulint start, ulint end, ullint *temp) {
	if (end - start == 1) {
		return 0;
	}
	
	ulint mid = (start + end) / 2;
	ullint invs = sortAndCount(v, start, mid, temp);
	invs += sortAndCount(v, mid, end, temp);
	invs += mergeAndCount(v, start, mid, end, temp);

	return invs;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ulint t, n, ii;
	ullint v[200000];
	ullint temp[200000];
	
	scanf("%lu", &t);
	while (t--) {
		scanf("%lu", &n);
		for (ii = 0; ii < n; ++ii) {
			scanf("%llu", &v[ii]);
		}
		
		printf("%llu\n", sortAndCount(v, 0, n, temp));
	}
}
