#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>

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

typedef long long int ullint;

#define MAX_BOXES	100
#define MAX_STONES	200
#define MOD 1000000007

int memo[MAX_BOXES][MAX_STONES + 1][MAX_STONES + 1];

int combine(int box, int stones, int used) {
	// Base case.
	if (box == 0) {
		if (stones) return 0;
		if (!used) return 1;
		return 0;
	}

	// Momoization (is it already calculated?)
	int &result = memo[box][stones][used];
	if (result != -1) return result;

	// Test current possibility.
    result = combine(box - 1, stones, used / 2);
	// Generate every possible number of stones for this box (0 .. stones). 
	if (stones) result += combine(box, stones - 1, used + 1);

	// Result should be mod 10^9 + 7 (as stated in the challenge text).
	result = (result % MOD);
	return result;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	memset(memo, -1, sizeof(memo));

	int s, b;
	while (cin >> s >> b) cout << combine(b - 1, s, 0) << endl;

    return 0;
}

