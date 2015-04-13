#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

	int n, ii;
	int a, b;
	int v14, v12, v34;

	scanf("%d", &n);
	if (n == 0) {
		printf("1\n");
		return 0;
	}

	v14 = v12 = v34 = 0;
	for (ii = 0; ii < n; ++ii) {
		scanf("%d/%d", &a, &b);
		if (a == 1) {
			if (b == 4) {
				++v14;
			} else {
				++v12;
			}
		} else {
			++v34;
		}
	}

	b = 1;

    // 3/4, using 1/4 or not.
    b += v34;
    v14 -= v34;
    
    // 1/2
	b += (v12 >> 1);
    if ((v12 & 1) != 0) {
        ++b;
        v14 -= 2;
    }
	
	// 1/4
    if (v14 > 0) {
	    b += ((v14 + 3) >> 2);
    }
    
	printf("%d\n", b);
	return 0;
}
