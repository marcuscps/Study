#include <iostream>
#include <cstdio>

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

typedef unsigned long long ull;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	ull n, l, x, b;
	int e;

	while (scanf("%llu", &n) == 1) {
		for (b = 10, x = n; x > 0; x /= 10, b *= 10);
		l = n * b;
		DEBUG("N = %llu  -  L = %llu  -  ", n, l);
		for (e = 0, x = 2; x < l; ++e, x <<= 1) DEBUG("  (%d) %llu", e + 1, x);

		x >>= 1;
		do {
			DEBUG("  (%d) %llu", e, x);
			++e;
			x <<= 1;
			for (l = x / b; l > n; l /= 10);
		} while (l != n);

		DEBUG("  (%d) %llu", e, x);
		printf("%d\n", e);
    }
    
    return 0;
}
