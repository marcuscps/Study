#include <iostream>
#include <cstdio>

using namespace std;

typedef unsigned long long int ullint;
typedef unsigned long int ulint;

int main() {
    ulint t, ii;
	ullint r;
	
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

	scanf("%lu", &t);
    for (ii = 1; ii <= t; ++ii) {
		scanf("%llu", &r);
		printf("Case %lu: %llu.25\n", ii, 4*r*r);
	}
    return 0;
}
