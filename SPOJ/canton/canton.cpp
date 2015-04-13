#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned long long int ullint;

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...) printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ullint t, n, dn, dr, d;
	scanf("%llu", &t);
	while (t--) {
		scanf("%llu", &n);
		dn = ceil((-1 + sqrt(8 * n + 1)) / 2);
		dr = dn * (dn - 1) / 2;
		d = n - dr;

		DEBUG("N = %llu    DN = %llu    DR = %llu    D = %llu    -> DN = %llu\n", n, dn, dr, d, dn + 1);

		dn += 1;

		if (dn % 2) {
			DEBUG("    %llu after the root (%llu) of the %llu diagonal (Odd).\n", d, dr, dn - 1);
			printf("TERM %llu IS %llu/%llu\n", n, d, dn - d);
		} else {
			DEBUG("    %llu after the root (%llu) of the %llu diagonal (Even).\n", d, dr, dn - 1);
			printf("TERM %llu IS %llu/%llu\n", n, dn - d, d);
		}
		
	}
}

