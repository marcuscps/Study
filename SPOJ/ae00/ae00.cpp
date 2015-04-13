#include <cstdio>

using namespace std;

typedef unsigned int uint;

//=================================================================================================
int main() {
	uint n, rects, a;
	scanf("%u", &n);
	rects = n;
	for (uint w = 1; w <= n / 2; ++w) {
		a = (n / w);
		if (a > w) {
			a = w;
		}
		if (a > 1) {
			rects += a - 1;
		}
	}
	printf("%u\n", rects);
}

