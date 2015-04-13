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

	// Multipliers: a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
	char mult[] = { 3, 2, 2, 2, 3, 2, 2, 2, 3, 2, 2, 2, 2, 2, 3, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2 };

	int t;
	char c;
	int i;
	unsigned int total;

	scanf("%d\n", &t);
	while (t--) {
		scanf("%c", &c);
		total = 1;
		while (c > 32) {
			// Convert to lowercase and normalize to 0 ~ 23.
			i = (c | 0x20) - 'a';
			total *= mult[i];
			scanf("%c", &c);
		}
		printf("%u\n", total);
	}

    return 0;
}

