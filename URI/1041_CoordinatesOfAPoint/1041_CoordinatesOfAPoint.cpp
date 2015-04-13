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

	float x, y;

	while (cin >> x >> y) {
		if (x == 0.0f) {
			if (y == 0.0f) {
				cout << "Origem" << endl;
				continue;
			}

			cout << "Eixo Y" << endl;
			continue;
		}

		if (y == 0.0f) {
			cout << "Eixo X" << endl;
			continue;
		}

		if (x > 0.0f) {
			if (y > 0.0f) cout << "Q1" << endl;
			else cout << "Q4" << endl;
			continue;
		}
		
		if (y > 0.0f) cout << "Q2" << endl;
		else cout << "Q3" << endl;
	}

    return 0;
}

