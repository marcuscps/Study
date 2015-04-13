// Based on Hjelmqvist, Sten (26 Mar 2012), Fast, memory efficient Levenshtein algorithm
// http://www.codeproject.com/Articles/13525/Fast-memory-efficient-Levenshtein-algorithm

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

inline int levenshteinDistance(char *s1, char *s2, int *a0, int *a1) {
    int *v0 = a0, *v1 = a1;
    int ii;
    int jj;
    int cost;
    
	for (; *s1 != 0 && *s1 == *s2; ++s1, ++s2);
    
	if (*s1 == *s2) return 0;
    
    int l1 = strlen(s1);
    int l2 = strlen(s2);

    if (l1 == 0) return l2;
    if (l2 == 0) return l1;
    
    for (ii = 0; ii <= l1 + 1; ++ii) {
        v0[ii] = ii;
    }

    for (ii = 0; ii < l1; ++ii) {
        v1[0] = ii + 1;
        
        for (jj = 0; jj < l2; ++jj) {
			if (s1[ii] == s2[jj]) {
				v1[jj + 1] = v0[jj];
			} else {
				v1[jj + 1] = min(min(v1[jj], v0[jj + 1]), v0[jj]) + 1;
			}
        }

        swap(v0, v1);
    }
	
    return v0[l2];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int t;
	char s1[2002], s2[2002];
	int a0[2002], a1[2002];

	scanf("%d", &t);
	while (t--) {
		scanf("%s", s1);
		scanf("%s", s2);		
        printf("%d\n", levenshteinDistance(s1, s2, a0, a1));
	}
	
	return 0;
}
