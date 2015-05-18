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

	const size_t maxSize = 1001;

	int k;
	string a, b;
	int eq[maxSize][maxSize];
	int res[maxSize][maxSize];

	for (size_t ii = 0; ii < maxSize; ++ii) eq[0][ii] = 0;
	for (size_t ii = 0; ii < maxSize; ++ii) res[0][ii] = 0;
	for (size_t kk = 0; kk < maxSize; ++kk) res[kk][0] = eq[kk][0] = 0;

	while (true) {
		cin >> k;
		if (k == 0) break;

		cin >> a >> b;

		size_t as = a.size();
		size_t bs = b.size();

		for (size_t kk = 1; kk <= bs; ++kk) {
			for (size_t ii = 1; ii <= as; ++ii) {
				if (a[ii - 1] == b[kk - 1]) {
					eq[kk][ii] = eq[kk - 1][ii - 1] + 1;
				} else {
					eq[kk][ii] = 0;
				}

				res[kk][ii] = std::max(res[kk][ii - 1], res[kk - 1][ii]);
				for (int size = k; size <= eq[kk][ii]; ++size) {
					res[kk][ii] = std::max(res[kk][ii], res[kk - size][ii - size] + size);
				}
			}
		}

		cout << res[bs][as] << endl;
	}

	return 0;
}

