#include <stdio.h>
#define SC scanf
#define PT printf

int main() {
    int t;
    char c,l;
    long long e;
    int a[9][8]={{4,4,2,1,1,4,4,2},{2,4,8,6},{3,9,7,1},{4,6},{5},{6},{7,9,3,1},{8,4,2,6},{9,1}};
    SC("%d", &t);
    while(t--){
		do{ l=c; SC("%c",&c); }while(c!=' ');
		SC("%lld", &e);
		(!e) ? PT("1\n") : (
		(l<'2') ? PT("%c\n",l) : (
		l-='0'+1 , PT("%d\n",a[l][(e-1)%a[0][l-1]])
		));
	}
    return 0;
}
