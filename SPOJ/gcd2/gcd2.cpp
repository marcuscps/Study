#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int gcd(int a, int b) {
    return (b==0) ? a : gcd(b, a%b);
}

int main() {
    int  t, a, ii, lb, r;
    char b[251];
    
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &a);
        scanf("%s", &b);
        if (a==0) {
            printf("%s\n",b);
            continue;
        }
        lb = strlen(b);
        for (r=0, ii=0; ii<lb; ++ii) {
            r = (r*10)+(b[ii]-'0');
            if (r > a) {
                r %= a;
            }
        }
        r %= a;
        printf("%d\n",gcd(a,r));
    }
    return 0;
}
