#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t, x;
	cin >> t;
	while (t) {
		x = t * t;
		t = (2 * t * x) + (3 * x) + t;
		t /= 6;

		cout << t << endl;
		cin >> t;
	}
}

