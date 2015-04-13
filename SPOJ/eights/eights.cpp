#include <cstdio>
#include <iostream>

using namespace std;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	unsigned int suffix[] = { 192, 442, 692, 942 };
	int t;
	long long unsigned int k;
	unsigned int pos;

	scanf("%d", &t);
	while (t--) {
		scanf("%llu", &k);
		k -= 1;
		pos = k % 4;
		k = k / 4;
		if (k) {
			printf("%llu", k);
		}
		printf("%u\n", suffix[pos]);
	}

	return 0;
}

