#include <iostream>
#include <cmath>

using namespace std;

// MAXPRIMES = sqrt( highestnumber ) + 1
// with highestNumber = 1 billion, MAXPRIMES = 31623
#define MAXPRIMES	31623

int primes[MAXPRIMES], numPrimes;

inline void genPrimes() {
	numPrimes = 0;

	for (int ii = 2; ii < MAXPRIMES; ++ii) {
		int lim = sqrt(ii) + 1;
		bool isPrime = true;
		for (int pIdx = 0; pIdx < numPrimes; ++pIdx) {
			int p = primes[pIdx];

			if (p > lim) {
				break;
			}
			if (ii % p == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) {
			primes[numPrimes++] = ii;
		}
	}
}



int main() {
	genPrimes();
	
	bool results[100000];
	for (int ii = 0; ii < 100000; ++ii) results[ii] = true;

	int t;
	cin >> t;
	while (t--) {
		int lo, hi;
		cin >> lo >> hi;

		if (lo < 2) lo = 2;

		for (int pIdx = 0; pIdx < numPrimes; ++pIdx) {
			int p = primes[pIdx];

			if (p * p > hi) break;

			int ii = (lo / p) * p;
			if (ii < lo) ii += p;
			if (ii == p) ii += p;

			for (; ii <= hi; ii += p) {
				results[ii - lo] = false;
			}
		}

		for (int ii = 0; ii <= hi - lo; ++ii) {
			if (results[ii]) {
				cout << lo + ii << endl;
			} else {
				results[ii] = true;
			}
		}
		
		if (t != 0) {
			cout << endl;
		}
	}
}

