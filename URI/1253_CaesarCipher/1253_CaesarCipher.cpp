#include <iostream>
#include <cstdio>

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

	int n, rs;
	string input;

	cin >> n;
	cin.ignore(1, '\n');
	while (n--) {
		getline(cin, input);
		cin >> rs;
		cin.ignore(1, '\n');

		if (rs == 0) {
			cout << input << endl;
			continue;
		}

		for (auto it = input.begin(); it != input.end(); ++it) {
			*it = *it - rs;
			if (*it < 'A') {
				*it += 26;
			}
		}

		cout << input << endl;
	}

    return 0;
}

