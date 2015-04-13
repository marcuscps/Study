#include <iostream>
#include <cstdio>
#include <cmath>

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	double r5 = sqrt(5);
	double t1 = (1.0 + r5) / 2.0;
	double t2 = (1.0 - r5) / 2.0;

	while (true) {
		// Desired numerator and denominator
		int dn, dd;
		scanf("%d %d", &dn, &dd);
		if (dn == 1 && dd == 1) break;

		// Left numerator and denominator
		int ln = 0, ld = 1;
		// Right numerator and denominator
		int rn = 1, rd = 0;
		// Current numerator and denominator
		int cn = 1, cd = 1;

		DEBUG("%d / %d = %lf\n", dn, dd, d);
		while (cn != dn || cd != dd) {
			// Comparing them
			if (cn * dd > cd * dn) {
				DEBUG("  <--- %d / %d = %f\n", cn, cd, c);
				printf("L");
				rn = cn;
				rd = cd;
			} else {
				DEBUG("  ---> %d / %d = %f\n", cn, cd, c);
				printf("R");
				ln = cn;
				ld = cd;
			}
			cn = ln + rn;
			cd = ld + rd;
		}
		printf("\n");
	}

    return 0;
}
