#include <iostream>
#include <cstdio>

#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

#if 0
int climbStairs(int n) {
	if (n < 0) return 0;
	if (n == 0) return 1;
	return climbStairs(n - 1) + climbStairs(n - 2) + climbStairs(n - 3);
}

#else

int climbStairsDP(int n, int map[]) {
	if (n < 0) return 0;
	if (n == 0) return 1;
	if (map[n] != -1) return map[n];
	map[n] = climbStairsDP(n - 1, map) + climbStairsDP(n - 2, map) + climbStairsDP(n - 3, map);
	return map[n];
}
#endif


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#if 0
	cout << climbStairs(1) << endl;
	cout << climbStairs(2) << endl;
	cout << climbStairs(3) << endl;
	cout << climbStairs(4) << endl;
	cout << climbStairs(5) << endl;
	cout << climbStairs(6) << endl;
	cout << climbStairs(7) << endl;
	cout << climbStairs(8) << endl;
	cout << climbStairs(9) << endl;
	cout << climbStairs(10) << endl;
	cout << climbStairs(11) << endl;
	cout << climbStairs(12) << endl;
	cout << climbStairs(13) << endl;
	cout << climbStairs(14) << endl;
	cout << climbStairs(15) << endl;
#else
	int *map = new int[16];
	for (int ii = 0; ii < 16; ++ii) map[ii] = -1;
	cout << climbStairsDP(1, map) << endl;
	cout << climbStairsDP(2, map) << endl;
	cout << climbStairsDP(3, map) << endl;
	cout << climbStairsDP(4, map) << endl;
	cout << climbStairsDP(5, map) << endl;
	cout << climbStairsDP(6, map) << endl;
	cout << climbStairsDP(7, map) << endl;
	cout << climbStairsDP(8, map) << endl;
	cout << climbStairsDP(9, map) << endl;
	cout << climbStairsDP(10, map) << endl;
	cout << climbStairsDP(11, map) << endl;
	cout << climbStairsDP(12, map) << endl;
	cout << climbStairsDP(13, map) << endl;
	cout << climbStairsDP(14, map) << endl;
	cout << climbStairsDP(15, map) << endl;
#endif

    return 0;
}
