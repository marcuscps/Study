#include <cstdio>
#include <iostream>

using namespace std;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	long long n, k, r, ii, dd;
	long long p;

	scanf("%d", &t);
	while (t--) {
		scanf("%lld %lld", &n, &k);
		r = n - k;
		n = k + r - 1;

		if (r > n / 2) {
			r = n - r;
		}

		p = 1;
		for (dd = 1; dd <= r; --n, ++dd) {
			p *= n;
			p /= dd;
		}

		printf("%lld\n", p);
	}

	return 0;
}

