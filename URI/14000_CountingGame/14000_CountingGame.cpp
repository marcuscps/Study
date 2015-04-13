#include <iostream>
#include <cstdio>

using namespace std;

inline bool isHit(unsigned long long int v) {
	if ((v % 7) == 0) return true;
	while (v) {
		if ((v % 10) == 7) return true;
		v /= 10;
	}
	return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	unsigned int n, m, k;

	while (true) {
		cin >> n >> m >> k;
		if (n == 0 && m == 0 && k == 0) break;

		unsigned int delta1 = (n - m) << 1;
		unsigned int delta2 = (m - 1) << 1;

		unsigned long long int v = m;
		unsigned long long int v0 = 0;
		while (k) {
			if (v != v0 && isHit(v)) {
				if (--k == 0) break;
			}
			v0 = v;
			v += delta1;
			if (v != v0 && isHit(v)) {
				if (--k == 0) break;
			}
			v0 = v;
			v += delta2;
		}

		cout << v << endl;
	}
    
	return 0;
}

