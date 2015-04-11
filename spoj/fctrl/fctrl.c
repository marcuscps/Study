#include <stdio.h>

int main()
{
	int five[] = {
		5,		25,
		125,		625,
		3125,		15625,
		78125,		390625,
		1953125,	9765625,
		48828125,	244140625
	};

	int t;
	scanf("%d", &t);
	while (t--) {
		int x, ii;
		scanf("%d", &x);

		int result = 0;
		for (ii = 0; ii < 12; ii++) {
			result += x / five[ii];
		}

		printf("%d\n", result);
	}
	return 0;
}

