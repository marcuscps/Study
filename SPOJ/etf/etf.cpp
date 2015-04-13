#include <iostream>
#include <cstdio>

using namespace std;

inline int fi(int n) { 
	int result = n; 
    for(int ii = 2; ii * ii <= n; ++ii) { 
		if (n % ii == 0) result -= result / ii; 
		while (n % ii == 0) {
			n /= ii; 
		}
	} 
    if (n > 1) {
		result -= result / n; 
	}
	return result; 
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);	

	int t, n;

	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		printf("%d\n", fi(n)); 
	}

	return 0;
}

