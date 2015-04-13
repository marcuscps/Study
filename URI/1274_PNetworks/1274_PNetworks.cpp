#include <iostream>
#include <cstdio>
#include <list>
#include <numeric>

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int v, size;
	bool possible;
	bool used[20];
	int destination[20], current[20], path_to[20];
	
	while (1) {
		list<int> result;

		cin >> size;
		if (size == 0) break;

		possible = true;
		fill(used, used + size, false);
		for (int ii = 0; ii < size; ++ii) {
			cin >> v;
			destination[ii] = --v;
			// Detecting impossible solution
			if (used[v] == true) possible = false;
			used[v] = true;
		}

		if (possible == false) {
			cout << "No solution" << endl;
			continue;
		}

		// Initializing paths
		iota(current, current + size, 0);
		iota(path_to, path_to + size, 0);

		for (int ii = 0; ii < size; ++ii) {
			int start = path_to[destination[ii]];
			if (ii == start) continue;

			for (int cur = start - 1; cur >= ii; --cur) {
				result.push_front(cur);
				swap(current[cur], current[cur + 1]);
				path_to[current[cur]] = cur;
				path_to[current[cur + 1]] = cur + 1;
			}
		}

		cout << result.size();
		for (auto it = result.begin(); it != result.end(); ++it) {
			cout << " " << (*it + 1);
		}
		cout << endl;
	}

    return 0;
}

