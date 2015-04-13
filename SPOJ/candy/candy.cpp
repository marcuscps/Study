#include <cstdio>
#include <iostream>

using namespace std;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int nums[10000];
	int n;
	int med;
	int moves;
	int num;
	while (1) {
		scanf("%d", &n);
		if (n == -1) {
			break;
		}

		long sum = 0;
		for (int ii = 0; ii < n; ++ii) {
			scanf("%d", &nums[ii]);
			sum += nums[ii];
		}

		if (sum % n) {
			printf("-1\n");
			continue;
		}

		med = sum / n;
		moves = 0;
		for (int ii = 0; ii < n; ++ii) {
			num = nums[ii];
			if (num > med) {
				moves += num - med;
			}
		}
		printf("%d\n", moves);
	}

	return 0;
}

