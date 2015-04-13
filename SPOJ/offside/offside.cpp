#include <cstdio>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int an, dn;
	int val;
	int closerAttacker;
	int count;
	
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    
	while (1) {
		scanf("%d %d", &an, &dn);
		if (an == 0 && dn == 0) break;
		
		closerAttacker = 10000;
		for (int ii = 0; ii < an; ++ii) {
			scanf("%d", &val);
			if (val < closerAttacker) {
				closerAttacker = val;
			}
		}
		
		count = 0;
		for (int ii = 0; ii < dn; ++ii) {
			scanf("%d", &val);
			if (val <= closerAttacker) {
                ++count;
			}
   		}
		
		if (count >= 2) {
			printf("N\n");
		} else {
			printf("Y\n");
		}
	}

	return 0;
}
