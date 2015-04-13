#include <iostream>
#include <cstdio>

using namespace std;

typedef unsigned long long int ullint;
typedef unsigned long int ulint;

int main() {
    char s[101];
    char o[201];
	int type;
	const int type_undef = 0;
	const int type_java = 1;
	const int type_cpp = 2;
	bool capsNext;
    bool error;
    int oii;
	
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    while (1) {
		if (scanf("%s", &s) != 1) {
			break;
		}

		type = type_undef;
		capsNext = false;
        error = false;
        oii = 0;
		for (int ii = 0; s[ii] != 0; ++ii) {
			if (s[ii] == '_') {
				if (type == type_java) {
                    error = true;
					break;
				}
    			if (ii == 0) {
                    error = true;
					break;
				}
    			if (capsNext == true) {
                    error = true;
					break;
				}
				type = type_cpp;
				capsNext = true;
			} else if (s[ii] >= 'A' && s[ii] <= 'Z') {
				if (type == type_cpp) {
                    error = true;
					break;
				}
				if (ii == 0) {
                    error = true;
					break;
				}
                o[oii++] = '_';
                o[oii++] = s[ii] - 'A' + 'a';
			} else if (capsNext) {
				capsNext = false;
                o[oii++] = s[ii] - 'a' + 'A';
			} else {
                o[oii++] = s[ii];
			}
		}
        o[oii++] = 0;
        
        if (error || capsNext) {
    		printf("Error!\n");
        } else {
        	printf("%s\n", o);
        }
	}
    return 0;
}
