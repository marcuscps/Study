#include <iostream>
#include <cstdio>
#include <string>

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

	string a, b;
	int carry;
	int val;
	int ncarries;

	while (1) {
		cin >> a >> b;
		if (a == "0" && b == "0") break;

		if (a.size() < b.size()) swap(a, b);

		string::reverse_iterator ita = a.rbegin();
		string::reverse_iterator itb = b.rbegin();
		carry = 0;
		ncarries = 0;
		while (ita != a.rend()) {
			val = carry + (*ita - '0');
			if (itb != b.rend()) {
				val += (*itb - '0');
				++itb;
			}
			if (val > 9) {
				carry = 1;
				++ncarries;
			} else {
				carry = 0;
			}
			++ita;
		}
		if (ncarries == 0) {
			cout << "No carry operation." << endl;
		} else if (ncarries == 1 ) {
			cout << "1 carry operation." << endl;
		} else {
			cout << ncarries << " carry operations." << endl;
		}
	}

    return 0;
}

