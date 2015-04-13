#include <iostream>
#include <cstdio>

using namespace std;

//=================================================================================================
inline int readValue(char *vec) {
    int ii = 0;
	char c;
    do {
	    if (scanf("%c", &c) != 1) {
            return 0;
	    };
    } while (c == ' ' || c == '\t' || c == '\n' || c == '\r');
	while (c >= '0' && c <= '9') {
		vec[ii++] = c - '0';
        if (scanf("%c", &c) != 1) {
            break;
        };
	}
	vec[ii] = 0;
	return ii;
}

//=================================================================================================
inline void printValue(char *vec, int len) {
    for (int ii = 0; ii < len; ++ii) {
    	printf("%c", (char)(vec[ii] + '0'));
	}
	printf("\n");
}

//=================================================================================================
inline bool numIsGreater(char *vec1, int len1, char *vec2, int len2) {
    if (len1 != len2) {
        return len1 < len2;
    }
    
    for (len1 = 0; len1 < len2; ++len1) {
        if (vec1[len1] != vec2[len1]) {
            return vec1[len1] < vec2[len1];
        }
    }
    
    return false;
}

//=================================================================================================
inline int nextPalin(char *vec, int pos1, int pos2) {
    while (1) {
        if (pos1 < 0) {
            --vec;
            vec[0] = vec[pos2] = 1;
            return 1;
        }
        
        if (vec[pos1] < 9) {
            vec[pos1] = vec[pos2] = vec[pos1] + 1;
            return 0;
        }
        
        vec[pos1--] = vec[pos2++] = 0;
    }
}

//=================================================================================================
int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    
#ifndef ONLINE_JUDGE
    printf("Reopening file...\n");
    freopen("input.txt", "r", stdin);
#endif
    
    int t, len;
    char num1v[1000010];
    char num2v[1000010];
    
    scanf("%d", &t);
    while (t--) {
        char *num1 = num1v + 2;
        char *num2 = num2v + 2;
        
        len = readValue(num1);
        if (len == 0) {
            printf("ERROR!\n");
            return 1;
        }
        int pos1 = (len - 1) / 2;
        int pos2 = len / 2;
        
        for (int ii = 0; ii < len; ++ii) {
            num2[ii] = num1[ii];
        }
        
        for (int ii = 0; ii <= pos1; ++ii) {
            num1[pos2 + ii] = num1[pos1 - ii];
        }
        
        if (numIsGreater(num2, len, num1, len)) {
            printValue(num1, len);
            continue;
        }
        
        int delta = nextPalin(num1, pos1, pos2);
        num1 -= delta;
        len += delta;
        printValue(num1, len);
    }
    
    return 0;
}
