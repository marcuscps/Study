#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

typedef std::map<float, unsigned int> Memo;


//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	Memo memo;
	double val = 0;
	for (unsigned int ii = 1; ii <= 276; ++ii) {
		val += 1.0/(ii + 1);
		memo.insert(make_pair(val, ii));
	}

	while (1) {
		float q;
		cin >> q;
		if (q == 0.00f) {
			break;
		}

		Memo::iterator it = memo.lower_bound(q);
		if (it != memo.end()) {
			cout << it->second << " card(s)" << endl;
		}
	}

	return 0;
}

