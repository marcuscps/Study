#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inv(int num) {
	int res = 0;
	while (num >= 1) {
		res = 10 * res + (num % 10);
		num /= 10;
	}
	return res;
}

int main() {
	int n, ii, jj;
	int a, b, t;
	char buf[30];

	scanf("%d", &n);
	for (; n > 0; --n) {
		scanf("%d %d", &a, &b);
		a = inv(a);
		b = inv(b);
		printf("%d\n", inv(a + b));
	}
}

