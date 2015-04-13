#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;

typedef map<string, int> CountMap;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int  t, n;
    char input[33 * 100001];
    CountMap map;
    pair<CountMap::iterator, bool> ret;

    scanf("%d", &t);
    while (t--) {
        scanf("%d ", &n);

        fread(input, 33 * sizeof(char), n, stdin);
        char *inputx = input;
        for (int ii = 0; ii < n; ++ii) {
            inputx[31] = 0;
            ++map[inputx];
            inputx += 33;
        }
        
        for (CountMap::iterator ii = map.begin(); ii != map.end(); ++ii) {
            printf("%s %d\n", ii->first.c_str(), ii->second);
        }
        printf("\n");

        map.clear();
    }
    return 0;
}
