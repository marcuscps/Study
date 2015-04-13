#include <iostream>
#include <cstdio>

using namespace std;

typedef unsigned long long int ullint;
typedef unsigned long int ulint;

int main() {
	ulint t;
	ullint acc;
	ullint num;
	char op;
	
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

	scanf("%lu", &t);
    while (t--) {
		acc = 0;
		num = 0;
		
        scanf("%llu", &acc);
		while (1) {
            scanf("%s", &op);
            if (op == '=') break;
            
            scanf("%llu", &num);

            switch (op) {
			case '+': acc += num; break;
			case '-': acc -= num; break;
			case '*': acc *= num; break;
			case '/': acc /= num; break;
			default: printf("ERROR!\n"); return 1;
			}
		}
		
		printf("%llu\n", acc);
	}
    return 0;
}
