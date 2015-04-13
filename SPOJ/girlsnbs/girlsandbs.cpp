#include <cstdio>
#include <iostream>

using namespace std;

//=================================================================================================
int main() {
	int g, b, v;

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	while (1) {
		scanf("%d %d", &g, &b);
		if (g == -1 && b == -1) { break; }
		if (b > g) { swap(b, g); }
		v = g/(b + 1);
		if (g % (b + 1)) ++v;
		printf("%d\n", v);
	}
	return 0;
}

