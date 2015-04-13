#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, v, result = 0;
	
	scanf("%d", &n);
	while (n--) {
		scanf("%d", &v);
        result ^= v;
    }
	printf("%d\n", result);
	
	return 0;
}
