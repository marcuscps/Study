#include <iostream>
#include <cstdio>
#include <stack>

#ifndef ONLINE_JUDGE
	#define DEBUG_ON
#endif
#ifdef DEBUG_ON
	#define DEBUG_ST(x)		x
	#define DEBUG(...)		printf("## " __VA_ARGS__)
	#define ODEBUG(...)		std::cout << "## " << __VA_ARGS__
	#define MDEBUG(...)		printf(__VA_ARGS__)
	#define OMDEBUG(...)	std::cout << __VA_ARGS__
#else
	#define DEBUG_ST(x)
	#define DEBUG(...)
	#define ODEBUG(...)
	#define MDEBUG(...)
	#define OMDEBUG(...)
#endif

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, v, front;
	bool answer;
    
    while (1) {
		cin >> n;
		if (n == 0) break;

		while (1) {
			stack<int> s;
			front = 1;
			answer = true;

			for (int ii = 0; ii < n; ++ii) {
				cin >> v;
				if (v == 0) break;
				if (answer == false) continue;

				ODEBUG("Expecting " << v);
				if (v == front) {
					OMDEBUG(" - Front coach!" << endl);
					++front;
					continue;
				}

				if (s.empty() == false) {
					if (s.top() == v) {
						OMDEBUG(" - Top of the Stack!" << endl); 
						s.pop();
						continue;
					}
					
					if (s.top() > v) {
						OMDEBUG(" - IMPOSSIBLE!" << endl); 
						answer = false;
						continue;
					}
				}

				OMDEBUG(" - Stacking up:"); 
				while (front < v) {
					OMDEBUG(" " << front); 
					s.push(front++);
				}
				++front;
				OMDEBUG(" - GOT IT!" << endl); 
			}
			
			if (v == 0) break;
			cout << ((answer == true) ? "Yes" : "No") << endl;
		}
		cout << endl;
    }
   
	cout.flush();
    return 0;
}

