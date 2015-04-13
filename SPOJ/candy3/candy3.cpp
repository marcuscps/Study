#include <cstdio>
#include <iostream>

using namespace std;

typedef unsigned long long ullong;

//=================================================================================================
int main() {
	ullong t, n, c, sum;
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scanf("%llu", &t);
	while (t--) {
		scanf("%llu", &n);
		sum = 0;
		for (ullong ii = 0; ii < n; ++ii) {
			scanf("%llu", &c);
			sum += c % n;
		}
		if (sum % n) {
			printf("NO\n");
		} else {
			printf("YES\n");
		}
	}

	return 0;
}

