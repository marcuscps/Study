#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf1[30];
char buf2[30];

int inv(int num) {
	sprintf(buf1, "%d", num);
	int t = strlen(buf1);
	int ii = 0;
	for (; ii < t && buf1[ii] == '0'; ++ii);
	int jj = 0;
	for (t = t - 1; t >= ii; --t) buf2[jj++] = buf1[t];
	buf2[jj] = '\0';
	return atoi(buf2);
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

