#include <iostream>
#include <stack>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    stack<int> s;
    int n, answer, v, expected;
    
    while(1) {
        scanf("%d", &n);
        if (n == 0) break;
        
        while (s.size() > 0) {
            s.pop();
        }
        
        expected = 1;
        answer = 0;
        for (int ii = 0; ii < n; ++ii) {
            scanf("%d", &v);
            if (answer == 0) {
                if (v == expected) {
                    ++expected;
                    continue;
                }
                
                while (s.empty() == false && s.top() == expected) {
                    s.pop();
                    ++expected;
                }

                if (s.empty() == false && s.top() < v) {
                    answer = 1;
                    continue;
                }
                
                s.push(v);
            }
        }
        
        if (answer == 0) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    
    return 0;
}
