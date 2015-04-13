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

inline ull revert(ull p) {
	ull r = 0;
	while (p > 0) {
		r = (10 * r) + (p % 10);
		p /= 10;
	}
	return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int t;
	ull p;
    
    scanf("%d", &t);
    while (t--) {
        scanf("%llu", &p);

		int n = 0;
		ull r;
		while (true) {
			r = revert(p);
			if (p == r) break;
			p += r;
			++n;
		}

        printf("%d %llu\n", n, p);
    }
    
    return 0;
}
