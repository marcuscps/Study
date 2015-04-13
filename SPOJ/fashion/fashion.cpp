#include <iostream>
//#include <cstdio>
//#include <algorithm>

using namespace std;

template<typename T> void insertionSort(T* vec, int size) {
	for (int ii = 1; ii < size; ++ii) {
		int jj = ii;
		T backup = vec[jj];
		for (; (vec[jj - 1] > backup) && (jj > 0); --jj) {
			vec[jj] = vec[jj - 1];
		}
		vec[jj] = backup;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	short int men[1001];
	short int women[1001];

	int t, x;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int ii = 0; ii < n; ++ii) {
			cin >> men[ii];
		}
		for (int ii = 0; ii < n; ++ii) {
			cin >> women[ii];
		}

		insertionSort(men, n);
		insertionSort(women, n);

		int h = 0;
		for (int ii = 0; ii < n; ++ii) {
			h += men[ii] * women[ii];
		}
		cout << h << endl;
	}
	return 0;
}

