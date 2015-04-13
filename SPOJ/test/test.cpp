#include <cstdio>
#include <iostream>

using namespace std;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	while (scanf("%d", &n) == 1) {
		if (n == 42) {
			break;
		}
		printf("%d\n", n);
	}

	return 0;
}

