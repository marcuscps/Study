#include <cstdio>
#include <iostream>

using namespace std;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	unsigned long long int t;

	scanf("%llu", &t);
	if ((t & (t - 1)) == 0) {
		printf("TAK\n");
	} else {
		printf("NIE\n");
	}

	return 0;
}

