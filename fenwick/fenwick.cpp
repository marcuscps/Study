#include <iostream>
#include <cstdio>
#include <iomanip>
#include <map>
#include <cstring>

using namespace std;

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

#define INDEX_0

int read(int *freqTree, int index) {
	ODEBUG("Reading index = " << index << "  -  " << (index + 1) << endl);
	int count = 0;
	while (index >= 0) {
		ODEBUG("  index = " << index << "  -  " << (index + 1) << endl);
		count += freqTree[index];
#ifdef INDEX_0
		/* index from ZERO */ index = (index & (index + 1)) - 1;
#else
		/* index from ONE  */ index -= index & -index;
#endif
	}
	return count;
}

void update(int *freqTree, size_t index, int delta, size_t maxValue) {
	ODEBUG("Updating index = " << index << "  -  " << (index + 1) << endl);
	while (index < maxValue) {
		ODEBUG("  index = " << index << "  -  " << (index + 1) << endl);
		freqTree[index] += delta;  
#ifdef INDEX_0
		/* index from ZERO */ index = index | (index + 1);
#else
		/* index from ONE  */ index += index & - index;
#endif
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	const size_t maxI = 16;
	int tree[maxI];
	memset(tree, 0, maxI * sizeof(int));

#ifdef INDEX_0
	size_t initial = 0;
#else
	size_t initial = 1;
#endif
	for (size_t ii = initial; ii < maxI; ++ii) {
		update(tree, ii, ii, maxI);
		cout << "        "; for (size_t jj = 0; jj < maxI; ++jj) { cout << fixed << setw(2) << jj << " "; } cout << endl;
		cout << "Vector: "; for (size_t jj = 0; jj < maxI; ++jj) { cout << fixed << setw(2) << tree[jj] << " "; } cout << endl;
	}
	
	for (size_t ii = initial; ii < maxI; ++ii) {
		read(tree, ii);
	}
}
