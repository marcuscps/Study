#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iterator>

#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)		printf("## " __VA_ARGS__)
	#define ODEBUG(...)		std::cout << "## " << __VA_ARGS__
	#define MDEBUG(...)		printf(__VA_ARGS__)
	#define OMDEBUG(...)	std::cout << __VA_ARGS__
#else
	#define DEBUG(...)
	#define ODEBUG(...)
	#define MDEBUG(...)
	#define OMDEBUG(...)
#endif

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	const int len = 100;
	unsigned int map[len + 1] = { 0 };
	map[0] = 1;

	int ii = 1;
	for (; ii <   5; ++ii) map[ii] = map[ii - 1];
	for (; ii <  10; ++ii) map[ii] = map[ii - 1] + map[ii - 5];
	for (; ii <  25; ++ii) map[ii] = map[ii - 1] + map[ii - 5] + map[ii - 10];
	for (; ii < 101; ++ii) map[ii] = map[ii - 1] + map[ii - 5] + map[ii - 10] + map[ii - 25];

	ostream_iterator<unsigned int> printer(cout, " ");

	cout << "Results: "; copy(map, map + len, printer); cout << endl;

    return 0;
}

