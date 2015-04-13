#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	unsigned int t, n, s;
    
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    scanf("%u", &t);
    while (t--) {
		scanf("%u %u", &n, &s);
        if (s == 0) {
            printf("Airborne wins.\n");
        } else {
            printf("Pagfloyd wins.\n");
        }
	}
    
    return 0;
}
