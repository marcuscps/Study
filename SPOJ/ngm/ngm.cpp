#include <cstdio>
#include <iostream>

using namespace std;

//=================================================================================================
int main() {
	int n;

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    while (scanf("%d", &n)== 1) {
		if (n % 10) {
			printf("1\n%d\n",n % 10);
		} else {
			printf("2\n");
		}
	}

	return 0;
}

