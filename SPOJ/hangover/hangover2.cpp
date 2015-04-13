#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	float memof[276];

	float val = 0;
	for (unsigned int ii = 1; ii <= 276; ++ii) {
		val += 1.0f/(ii + 1);
		memof[ii - 1] = val;
	}
	vector<float> memo(memof, memof + 277);

	while (1) {
		float q;
		cin >> q;
		if (q == 0.00f) {
			break;
		}

		vector<float>::iterator it = std::lower_bound(memo.begin(), memo.end(), q);
		if (it != memo.end()) {
			cout << (1 + it - memo.begin()) << " card(s)" << endl;
		}
	}

	return 0;
}

