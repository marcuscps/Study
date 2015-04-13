#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

	int t;
	long long int v;

	scanf("%d", &t);
	while (t--) {
		scanf("%lld", &v);
		v = ((3 * v * v) + v) / 2;
		v %= 1000007;
		printf("%lld\n", v);
    }
	
	return 0;
}
