#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		int x, y;
		cin >> x >> y;

		if (x == y) {
			y = x / 2;
			x = x % 2;
			cout << (4 * y + x) << endl;
		} else if (x == y + 2) {
			y = y % 2;
			x = (x / 2) - 1;
			if (x < 0) x = 0;
			cout << (2 + (4 * x) + y) << endl;
		} else {
			cout << "No Number" << endl;
		}
	}
}
