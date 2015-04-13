#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG_ST(x)		x
	#define ODEBUG(...)		cout << "## " << __VA_ARGS__
	#define OMDEBUG(...)	cout << __VA_ARGS__
#else
	#define DEBUG_ST(x)
	#define ODEBUG(...)
	#define OMDEBUG(...)
#endif

int findLeftEnd(int *v, int n) {
	for (int ii = 1; ii < n; ++ii) {
		if (v[ii] < v[ii - 1]) return ii - 1;
	}
	return n - 1;
}

int findRightStart(int *v, int n) {
	for (int ii = n - 2; ii >= 0; --ii) {
		if (v[ii] > v[ii + 1]) return ii + 1;
	}
	return 0;
}

int shrinkLeft(int *v, int n, int index, int minValue) {
	while (index >= 0 && v[index] > minValue) --index;
	return index;
}

int shrinkRight(int *v, int n, int index, int maxValue) {
	while (index < n && v[index] < maxValue) ++index;
	return index;
}

pair<int, int> findUnorderedSequence(int *v, int n) {
	int leftEnd = findLeftEnd(v, n);
	if (leftEnd >= n - 1) return make_pair(-1, -1); // sorted

	int rightStart = findRightStart(v, n);
	ODEBUG("Range: " << leftEnd << " " << rightStart << endl);

	int minIndex = leftEnd + 1;
	int maxIndex = rightStart - 1;
	for (int ii = leftEnd; ii <= rightStart; ++ii) {
		if (v[ii] < v[minIndex]) minIndex = ii;
		if (v[ii] > v[maxIndex]) maxIndex = ii;
	}
	ODEBUG("Min: v[" << minIndex << "] = " << v[minIndex] << "  -  Max: v[" << maxIndex << "] = " << v[maxIndex] << endl);

	leftEnd = shrinkLeft(v, n, leftEnd, v[minIndex]);
	rightStart = shrinkRight(v, n, rightStart, v[maxIndex]);
	ODEBUG("Range: " << leftEnd << " " << rightStart << endl);

	return make_pair(leftEnd + 1, rightStart - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int v[30];

	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int ii = 0; ii < n; ++ii) cin >> v[ii];

		ODEBUG("Index:"); DEBUG_ST(for (int ii = 0; ii < n; ++ii) OMDEBUG(setw(3) << ii)); OMDEBUG(endl);
		ODEBUG("Value:"); DEBUG_ST(for (int ii = 0; ii < n; ++ii) OMDEBUG(setw(3) << v[ii])); OMDEBUG(endl);

		auto res = findUnorderedSequence(v, n);
		cout << res.first << " " << res.second << endl;
	}

    return 0;
}

