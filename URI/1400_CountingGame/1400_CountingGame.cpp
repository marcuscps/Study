#include <iostream>
#include <cstdio>

using namespace std;

typedef unsigned long long int ullint;
typedef unsigned int uint;

inline bool isHit(ullint v) {
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

		uint delta1 = (n - m) << 1;
		uint delta2 = (m - 1) << 1;

		ullint v = m;
		ullint v0 = 0;
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

