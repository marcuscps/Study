#include <cstdio>
#include <iostream>
#include <cmath>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	long long int n;
    double f, i;
	
	while (1) {
		scanf("%lld", &n);
		if (n == -1) break;
		
		f = modf((sqrt(((--n) * 4 / 3) + 1) - 1) / 2, &i);
		if (f == 0.0) {
			printf("Y\n");
		} else {
			printf("N\n");
		}
	}
 
	return 0;
}
