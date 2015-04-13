#include <iostream>
#include <string>

#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

int strDistance(string &a, string &b) {
	if (a.size() == 0) return b.size();
	if (b.size() == 0) return a.size();


	int l0a[17];
	int l1a[17];
	 
	for (size_t ii = 0; ii <= a.size(); ++ii) {
		l0a[ii] = ii;
	}

	int *l0 = l0a;
	int *l1 = l1a;
	for (size_t ii = 1; ii <= b.size(); ++ii) {
		l1[0] = ii;

		for (size_t jj = 1; jj <= a.size(); ++jj) {
			if (a[jj - 1] == b[ii - 1]) {
				l1[jj] = l0[jj - 1];
			} else {
				l1[jj] = min(min(l1[jj - 1], l0[jj]), l0[jj - 1]) + 1;
			}
		}
		swap(l0, l1);
	}

	return l0[a.size()];
}

int main() {

	while (cin.eof() == false) {
		string
	}

	return 0;
}
