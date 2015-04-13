#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    unsigned long long lastN = 0, n;
    unsigned long long ii, jj;
    bool eq;
    char format[50];
    char *niddle = 0;
    int  *niddleDelta = 0;
    char c;

    while (scanf("%llu ", &n) == 1) {
        if (n > lastN) {
            if (lastN != 0) {
                delete [] niddle;
                delete [] niddleDelta;
                lastN = 0;
            }
            if (n > 0) {
                niddle = new char[n + 1];
                niddleDelta = new int[n + 1];
                lastN = n;
            }
        }
        //n += 1;
        sprintf(format, "%%%llu[^\n]s", n);
        scanf(format, niddle);
        
#if 0
        niddleDelta[0] = 0;
        eq = true;
        for (ii = 1, jj = 0; ii < n; ++ii) {
            if (niddle[ii] == niddle[jj]) {
                niddleDelta[ii] = jj++;
            } else {
                niddleDelta[ii] = jj;
                jj = 0;
            }
            if (niddle[ii] != niddle[ii - 1]) {
                eq = false;
            }
        }
#endif
        niddleDelta[0] = -1;
        for(ii = 0; ii < n; ++ii) {
		    niddleDelta[ii + 1] = niddleDelta[ii] + 1;
		    while(niddleDelta[ii + 1] > 0 && niddle[ii] != niddle[niddleDelta[ii + 1] - 1]) {
    			niddleDelta[ii + 1] = niddleDelta[niddleDelta[ii + 1] - 1] + 1;
		    }
	    }

#if 0
        printf("Niddle: \"%s\"\n", niddle);
        printf("Niddle: ");
        for (ii = 0; ii < n; ++ii) {
            printf(" %c", niddle[ii]);
        }
        printf("\n");
        printf("Delta:  ");
        for (ii = 0; ii <= n; ++ii) {
            printf("% 2d", niddleDelta[ii]);
        }
        printf("\n");
#endif
        
        c = '\n';
        while (c == ' ' || c == '\n' || c == '\r') {
            if (scanf("%c", &c) == 0) break;
        }
        
        ii = 0;
        jj = 0;
        while (c != '\n' && c != '\r') {
            while (1) {
                if (c == niddle[jj]) {
                    //printf("  '%c' found.\n", c);
                    ++jj;
                    if (jj == n) {
                        //printf("RESULT: ");
                        printf("%llu\n", ii - jj + 1);
                        jj = niddleDelta[jj];
                        //printf("BACK TO: %llu\n", jj);
                    }
                    break;
                } else {
                    if (jj == 0) {
                        //printf("  '%c' NOT found. ", c);
                        //printf("BACK TO: %llu\n", jj);
                        break;
                    } else {
                        jj = niddleDelta[jj];
                        //printf("BACK TO: %llu\n", jj);
                    }
                }
            }
            ++ii;
            if (scanf("%c", &c) != 1) break;
        }
        
        printf("\n");
    }
    
    return 0;
}
