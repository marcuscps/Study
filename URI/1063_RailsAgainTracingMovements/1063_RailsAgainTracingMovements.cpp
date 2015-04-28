#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>

#ifndef ONLINE_JUDGE
//	#define DEBUG_ON
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

	size_t n, ii, nextI, nextO;
	char input[26], output[26];
	char cI, cO;
	stack<char> station;

	while (true) {
		cin >> n;
		if (n == 0) break;
		
		for (ii = 0; ii < n; ++ii) cin >> input[ii];
		for (ii = 0; ii < n; ++ii) cin >> output[ii];

		// Clean up the stack.
		while (station.empty() == false) station.pop();

		nextI = nextO = 0;
		while (nextI < n) {
			cI = input[nextI];
			cO = output[nextO];

			if (cI == cO) {
				cout << "IR";
				++nextI;
				++nextO;
				continue;
			}

			if (station.empty() == false && station.top() == cO) {
				station.pop();
				cout << "R";
				++nextO;
			} else {
				cout << "I";
				station.push(cI);
				++nextI;
			}
		}

		while (station.empty() == false) {
			if (station.top() == output[nextO]) {
				station.pop();
				cout << "R";
				++nextO;
			} else {
				cout << " Impossible";
				break;
			}
		}

		cout << endl;
	}

    return 0;
}

