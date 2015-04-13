#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	unsigned int l;
	double a;
	double epsilon = 10e-10;

	scanf("%u", &l);
	while (l != 0) {
		a = l * l / 2.0 / M_PI;
		printf("%.02f\n", a + epsilon);
		scanf("%u", &l);
	}

	return 0;
}

