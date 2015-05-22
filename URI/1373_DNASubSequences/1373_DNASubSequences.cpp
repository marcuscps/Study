#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	const size_t maxSize = 1001;

	int k;
	size_t ii, kk;
	string a, b;
	int m[maxSize][maxSize];
	int t, kmax, suffix;
	size_t as, bs;

	for (ii = 0; ii < maxSize; ++ii) m[0][ii] = 0;
	for (ii = 0; ii < maxSize; ++ii) m[ii][0] = 0;

	while (1) {
		cin >> k;
		if (k == 0) break;

		cin >> a >> b;

		as = a.size();
		bs = b.size();

		for (kk = 1; kk <= bs; ++kk) {
			for (ii = 1; ii <= as; ++ii) {
				if (a[ii - 1] == b[kk - 1]) {
					m[kk][ii] = m[kk - 1][ii - 1] + 1;
				} else {
					m[kk][ii] = 0;
				}
			}
		}

		for (kk = 1; kk <= bs; ++kk) {
			for (ii = 1; ii <= as; ++ii) {
				t = max(m[kk][ii - 1], m[kk - 1][ii]);
				kmax = m[kk][ii];
				for (suffix = k; suffix <= kmax; ++suffix) {
					t = max(t, m[kk - suffix][ii - suffix] + suffix);
				}
				m[kk][ii] = t;
			}
		}

		cout << m[bs][as] << endl;
	}

	return 0;
}

