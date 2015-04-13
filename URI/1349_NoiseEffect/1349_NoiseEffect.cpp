#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

#ifndef ONLINE_JUDGE
	#define DEBUG_ON
#endif
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

size_t test(int std_image[400][400], int scan_image[400][400], size_t l) {
	size_t best, hits;
	size_t l1 = l - 1;

	// 1
	best = 0;
	for (size_t ii = 0; ii < l; ++ii) {
		for (size_t jj = 0; jj < l; ++jj) {
			if (abs(scan_image[ii][jj] - std_image[ii][jj]) <= 100) ++best;
		}
	}
	ODEBUG("  0 deg --> " << best << endl);

	// 2
	hits = 0;
	for (size_t ii = 0; ii < l; ++ii) {
		for (size_t jj = 0; jj < l; ++jj) {
			if (abs(scan_image[jj][l1 - ii] - std_image[ii][jj]) <= 100) ++hits;
		}
	}
	if (hits > best) best = hits;
	ODEBUG(" 90 deg --> " << hits << endl);
	
	// 3
	hits = 0;
	for (size_t ii = 0; ii < l; ++ii) {
		for (size_t jj = 0; jj < l; ++jj) {
			if (abs(scan_image[l1 - ii][l1 - jj] - std_image[ii][jj]) <= 100) ++hits;
		}
	}
	if (hits > best) best = hits;
	ODEBUG("180 deg --> " << hits << endl);

	// 4
	hits = 0;
	for (size_t ii = 0; ii < l; ++ii) {
		for (size_t jj = 0; jj < l; ++jj) {
			if (abs(scan_image[l1 - jj][ii] - std_image[ii][jj]) <= 100) ++hits;
		}
	}
	if (hits > best) best = hits;
	ODEBUG("270 deg --> " << hits << endl);

	return best;
}

void flip(int img[400][400], size_t l) {
	ODEBUG("Flipping..." << endl);
	for (size_t ii = 0; ii < l; ++ii) {
		for (size_t p = 0, f = l - 1; p < f; ++p, --f) {
			swap(img[ii][p], img[ii][f]);
		}
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	size_t l;
	int std_image[400][400];
	int scan_image[400][400];
	size_t hits, best;

	while (1) {
		cin >> l;
		if (l == 0) break;


		for (size_t ii = 0; ii < l; ++ii) {
			for (size_t jj = 0; jj < l; ++jj) {
				cin >> std_image[ii][jj];
			}
		}

		for (size_t ii = 0; ii < l; ++ii) {
			for (size_t jj = 0; jj < l; ++jj) {
				cin >> scan_image[ii][jj];
			}
		}

		best = test(std_image, scan_image, l);
		flip(std_image, l);
		hits = test(std_image, scan_image, l);
		if (hits > best) best = hits;

		ODEBUG("Best --> " << best << endl);
		cout << fixed << setprecision(2) << ((100.0f * best) / (l * l)) << endl;
	}

    return 0;
}

