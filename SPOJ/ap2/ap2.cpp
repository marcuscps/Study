#include <cstdio>
#include <iostream>

using namespace std;

typedef long long int llint;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	llint t2, tn2, sum, n, r;
	llint ii, t0;

	scanf("%d", &t);
	while (t--) {
		scanf("%lld %lld %lld", &t2, &tn2, &sum);
		n = 2 * sum / (t2 + tn2);
		r = (tn2 - t2) / (n - 5);
		t0 = t2 - (2 * r);
		printf("%lld\n%lld", n, t0);
		t0 += r;
		for (ii = 1; ii < n; ++ii, t0 += r) {
			printf(" %lld", t0);
		}
		printf("\n");
	}

	return 0;
}

