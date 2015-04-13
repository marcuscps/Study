#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;


void solveIt(int n, int b0, bool braces) {
	if (n == 0) { printf("(0)"); return; }
	if (n == 1) { printf("");    return; }

	if (braces == true) {
		printf("(");
	}
	bool first = true;
	for	(int b = b0, v = 1 << b; b >= 0; --b, v >>= 1) {
		if ((n & v) != 0) {
			if (first == false) { printf("+"); }
			printf("2");
			solveIt(b, b/2, true);
			first = false;
		}
	}
	if (braces == true) {
		printf(")");
	}
}


//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;

	while (scanf("%d", &n) == 1) {
		printf("%d=", n);
		solveIt(n, 14, false);
		printf("\n");
	}

	return 0;
}

