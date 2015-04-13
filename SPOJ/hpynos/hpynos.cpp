#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

	int  n;
	int  from[900];
	int  to[900];
	int  top = 0;
	int  rounds = 1;
	int  a, b;

	scanf("%d", &n);
	while (n != 1) {
		a = n;
		n = 0;
		while (a != 0) {
			b = a % 10;
			n += b * b;
			a /= 10;
		}
		
		a = from[n];
		if (a < top && to[a] == n) {
			rounds = -1;
			break;
		}
		
		from[n] = top;
		to[top++] = n;
		++round;
	}
	
	printf("%d\n", n);
	return 0;
}
