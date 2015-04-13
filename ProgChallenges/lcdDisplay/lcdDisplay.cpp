#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

//#define DEBUG(...) printf( __VA_ARGS__ )
#define DEBUG(...)

#define SB(x) (1 << x)

const int digits[] = {
	/* 0 */ SB(1) | SB(3) | SB(5) | SB(9) | SB(11) | SB(13),
	/* 1 */ SB(5) | SB(11),
	/* 2 */ SB(1) | SB(5) | SB(7) | SB(9) | SB(13),
	/* 3 */ SB(1) | SB(5) | SB(7) | SB(11) | SB(13),
	/* 4 */ SB(3) | SB(5) | SB(7) | SB(11),
	/* 5 */ SB(1) | SB(3) | SB(7) | SB(11) | SB(13),
	/* 6 */ SB(1) | SB(3) | SB(7) | SB(9) | SB(11) | SB(13),
	/* 7 */ SB(1) | SB(5) | SB(11),
	/* 8 */ SB(1) | SB(3) | SB(5) | SB(7) | SB(9) | SB(11) | SB(13),
	/* 9 */ SB(1) | SB(3) | SB(5) | SB(7) | SB(11) | SB(13)
};

void printNumber(int d, int s, int l) {
	d = digits[d];
	l *= 3;
	d = d >> l;

	char lc = '|', mc = '-', rc = '|';
	if ((d & 1) == 0) lc = ' ';
	if ((d & 2) == 0) mc = ' ';
	if ((d & 4) == 0) rc = ' ';

	printf("%c", lc);
	for (int ii = 0; ii < s; ++ii) {
		printf("%c", mc);
	}
	printf("%c", rc);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int s, n, d;
	char nums[10];

	scanf("%d %d", &s, &n);
	while (s != 0 && n != 0) {
		for (d = 0; n != 0; ++d) {
			nums[d] = n % 10;
			n /= 10;
		}

		DEBUG("Split: ");
		for (int ii = d - 1; ii >= 0; --ii) {
			DEBUG("%d ", nums[ii]);
		}
		DEBUG("\n");

		int l = 0;
		int l1 = 0;
		int l2 = s;
		int l3 = l2 + 1;
		int l4 = l3 + s;
		for (int kk = 0; kk < (2 * s) + 3; ++kk) {
			for (int ii = d - 1; ii >= 0; --ii) {
				printNumber(nums[ii], s, l);
				if (ii != 0) printf(" ");
			}
			printf("\n");

			if (kk == l1 || kk == l2 || kk == l3 || kk == l4) {
				++l;
			}
		}
		printf("\n");

		scanf("%u %u", &s, &n);
	}

	return 0;
}
