#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>

#define DEBUG_ON
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

inline int getBit(vector<int> &numbers, int idx, int bitn) {
	return ((numbers[idx] >> bitn) & 1);
}

int findMissing(vector<int> &numbers) {
	vector<int> zeros, ones;
	vector<int> current(numbers.size());

	// Fill the current vector with a sequence from zero to numbers.size() - 1.
	iota(current.begin(), current.end(), 0); 

	int missing = 0, bitn = 0;
	while (current.size() > 0) {
		for (vector<int>::iterator it = current.begin(); it != current.end(); ++it) {
			int ii = *it;
			int bit = getBit(numbers, ii, bitn);
			if (bit) {
				ones.push_back(ii);
			} else {
				zeros.push_back(ii);
			}
		}

		if (zeros.size() > ones.size()) {
			missing |= (1 << bitn);
			swap(ones, current);
		} else {
			swap(zeros, current);
		}

		++bitn;
		zeros.clear();
		ones.clear();
	}

	return missing;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		ODEBUG("Test number " << (t + 1) << endl);
		vector<int> numbers;
		int n;

		cin >> n;
		numbers.reserve(n);
		for (int ii = 0; ii < n; ++ii) {
			int v;
			cin >> v;
			numbers.push_back(v);
		}

		cout << findMissing(numbers) << endl;
	}

    return 0;
}

