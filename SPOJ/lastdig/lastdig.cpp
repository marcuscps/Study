#include <cstdio>
#include <iostream>

using namespace std;

typedef unsigned int uint;

uint oneDigExp(uint b, uint e) {
	uint ret;
	b = b % 10;
	if (e == 0) {
		return 1;
	}
	
	if (b < 2) {
		return b;
	}

	if ((e % 2) != 0) {
		ret = b * oneDigExp(b, e - 1);
	} else {
		ret = oneDigExp(b, e / 2);
		ret = ret * ret;
	}
	return ret % 10;
}

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	uint t, b, e;
	scanf("%u", &t);
	while (t--) {
		scanf("%u %u", &b, &e);
		printf("%u\n", oneDigExp(b, e));
	}
}

