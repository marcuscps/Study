#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>

#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG_ST(x)		x
	#define DEBUG(...)		printf("## " __VA_ARGS__)
	#define ODEBUG(...)		std::cout << "## " << __VA_ARGS__
	#define MDEBUG(...)		printf(__VA_ARGS__)
	#define OMDEBUG(...)	std::cout << __VA_ARGS__
#else
	#define DEBUG(...)
	#define ODEBUG(...)
	#define MDEBUG(...)
	#define OMDEBUG(...)
	#define DEBUG_ST(x)
#endif

using namespace std;

int searchRotated(vector<int> &vec, size_t l, size_t h, int v) {
	size_t m = (l + h) / 2;

	ODEBUG("Range:  ");
	DEBUG_ST(
		for (size_t ii = 0; ii <= vec.size(); ++ii) {
			string s; s.reserve(3);
			if (ii == l) s += "L";
			if (ii == m) s += "M";
			if (ii == h) s += "H";
			OMDEBUG(setw(3) << s << " ");
		}
	);

	if (h <= l) {
		OMDEBUG("  -  Empty interval  ->  NOT Found!" << endl);
		return -1;
	}

	if (vec[m] == v) {
		OMDEBUG("  ->  Found " << v << " @ " << m << endl);
		return m;
	}

	if (vec[l] < vec[m] || vec[m] > vec[h - 1]) {
		// Left is normally ordered
		OMDEBUG("  -  Left is N.O.");

		if (vec[l] <= v && v < vec[m]) {
			OMDEBUG("  -  L <= v < M  ->  Left!" << endl);
			return searchRotated(vec, l, m, v);
		} else {
			OMDEBUG("  -  Not on left  ->  Right!" << endl);
			return searchRotated(vec, m + 1, h, v);
		}
	}

	if (vec[l] > vec[m] || vec[m] < vec[h - 1]) {
		// Right is normally ordered
		OMDEBUG("  -  Right is N.O.");

		if (vec[m] < v && v <= vec[h - 1]) {
			OMDEBUG("  -  M < v <= H  ->  Right!" << endl);
			return searchRotated(vec, m + 1, h, v);
			l = m + 1;
		} else {
			OMDEBUG("  -  Not on right  ->  Left!" << endl);
			return searchRotated(vec, l, m, v);
		}
	}

	OMDEBUG("  -  Can't determine N.O. side." << endl);
	if (l < m) {
		int found;
		if ((found = searchRotated(vec, l, m, v)) != -1) {
			return found;
		}
	}
	if (h > m + 1) {
		return searchRotated(vec, m + 1, h, v);
	}
	return -1;
}

int searchRotated(vector<int> &vec, int v) {
	ODEBUG("Searching for " << v << ": " << endl);
	ODEBUG("Index:  "); DEBUG_ST( for (size_t ii = 0; ii <= vec.size(); ++ii) OMDEBUG(setw(3) << ii << " ") ); OMDEBUG(endl);
	ODEBUG("Vector: "); DEBUG_ST( for (size_t ii = 0; ii <  vec.size(); ++ii) OMDEBUG(setw(3) << vec[ii] << " ") ); OMDEBUG(endl);
	return searchRotated(vec, 0, vec.size(), v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;

		vector<int> vec;
		vec.reserve(n);
		
		for (int ii = 0; ii < n; ++ii) {
			int v;
			cin >> v;
			vec.push_back(v);
		}

		while (k--) {
			int v;
			cin >> v;
			cout << searchRotated(vec, v) << endl;
		}
	}

    return 0;
}

