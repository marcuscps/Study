#include <cstdio>
#include <iostream>

using namespace std;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	char p[5001];
	int size;
	char c;
	int val;
	unsigned long long decodings;
	unsigned long long decodings1;
	unsigned long long decodings2;

	while (1) {
		c = '\n';
		do {
			if (scanf("%c", &c) == 0) break;
		} while (c == ' ' || (c >= '\t' && c <= '\r'));
		for (size = 0; size < 5001; ++size) {
			if (c < '0' || c > '9') break;
			p[size] = c - '0';
			if (scanf("%c", &c) == 0) break;
		}
		p[size] = 0;
		if (p[0] == 0) {
			break;
		}

		decodings1 = decodings2 = 1;
		val = 0;
		for (int ii = 1; ii < size; ++ii) {
			val = (10 * p[ii - 1]) + p[ii];

			decodings = (p[ii] != 0) ? decodings1 : 0;
			if (val <= 26 && val > 9) {
				decodings += decodings2;
			}
			
			decodings2 = decodings1;
			decodings1 = decodings;
		}
		printf("%llu\n", decodings);
	}

	return 0;
}

