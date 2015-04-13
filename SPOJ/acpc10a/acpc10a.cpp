#include <cstdio>

using namespace std;

//=================================================================================================
int main() {
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
	
	int a, b, c, val;
	while (1) {
		scanf("%d %d %d", &a, &b, &c);
		if (a == 0 && b == 0 && c == 0) {
			break;
		}

		val = (c - b);
		if ((b - a) == val) {
			printf("AP %d\n", (c + val));
			continue;
		}

		val = (c / b);
		printf("GP %d\n", (c * val));
	}

	return 0;
}
