#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t;
	double a, b, c, d, s, maxArea;

	scanf("%d", &t);
	while (t--) {
		scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
		s = a + b + c + d;
		s /= 2.0;
		maxArea = sqrt((s - a) * (s - b) * (s - c) * (s - d));
		printf("%.02lf\n", maxArea);
	}
	
	return 0;
}
