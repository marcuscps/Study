#include <cstdio>
#include <iostream>

using namespace std;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int p, n, ii, seqn;
	char s[41];
	int a[8] = {0};

	scanf("%d", &p);
	while (p--) {
		scanf("%d %s", &n, &s);

		s[0] = (s[0] == 'T') ? 0 : 1;
		s[1] = (s[1] == 'T') ? 0 : 1;
		s[2] = (s[2] == 'T') ? 0 : 1;
		seqn = (s[0] << 2) | (s[1] << 1) | (s[2]);
		++a[seqn];
		for (ii = 3; ii < 40; ++ii) {
			seqn = (((seqn << 1) | ((s[ii] == 'T') ? 0 : 1)) & 0x00000007);
			++a[seqn];
		}

		printf("%d", n);
		for (ii = 0; ii < 8; ++ii) {
			printf(" %d", a[ii]);
			a[ii] = 0;
		}
		printf("\n");

	}

	return 0;
}

