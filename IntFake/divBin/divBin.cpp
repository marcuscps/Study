#include <iostream>
#include <cstdio>

#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)		printf("## " __VA_ARGS__);
	#define ODEBUG(...)		std::cout << "## " << __VA_ARGS__
	#define EDEBUG(...)		std::cerr << "## " << __VA_ARGS__

	#define MDEBUG(...)		printf(__VA_ARGS__);
	#define OMDEBUG(...)	std::cout << __VA_ARGS__
	#define EMDEBUG(...)	std::cerr << __VA_ARGS__
#else
	#define DEBUG(...)
	#define ODEBUG(...)
	#define EDEBUG(...)

	#define MDEBUG(...)
	#define OMDEBUG(...)
	#define EMDEBUG(...)
#endif

using namespace std;

int hibit(int n);

void bin(int n) {
	int hbit = hibit(n);
	do {
		if (n & hbit) printf("1");
		else printf("0");
		hbit >>= 1;
	} while (hbit);
}

int hibit(int n) {
    n |= (n >>  1);
    n |= (n >>  2);
    n |= (n >>  4);
    n |= (n >>  8);
    n |= (n >> 16);
//    n |= (n >> 32);
    return n - (n >> 1);
}

int divBin(int n, int d) {
	int hbit = hibit(n);
	int num = 0;
	int result = 0;

	while (hbit) {
		num <<= 1;
		if (n & hbit) {
			num |= 1;
		}

		result <<= 1;
		if (num >= d) {
			result |= 1;
			num -= d;
		}

		hbit >>= 1;
	}
	return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t, n, d, r;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &d);
		r = divBin(n, d);
		DEBUG("Result: %d\n", r);
		bin(r);
		printf("\n");
	}

    return 0;
}

