#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	string ys;
	bool first = true;
	int mod4, mod100, mod400, mod15, mod55, leap;

	while (getline(cin, ys)) {
		if (!first) cout << "\n";
		first = false;

		mod4 = mod100 = mod400 = mod15 = mod55 = leap = 0;
		for (size_t ii = 0; ii < ys.size(); ++ii) {
			int v = static_cast<int>(ys[ii] - '0');
			mod4   = ((  mod4 * 10) + v) %   4;
			mod15  = (( mod15 * 10) + v) %  15;
			mod55  = (( mod55 * 10) + v) %  55;
			mod100 = ((mod100 * 10) + v) % 100;
			mod400 = ((mod400 * 10) + v) % 400;
		}

		bool isLeap = ((mod4 == 0 && mod100 != 0) || mod400 == 0);

		bool ordinary = true;
		if (isLeap) {
			cout << "This is leap year.\n";
			ordinary = false;
		}
		if (mod15 == 0) {
			cout << "This is huluculu festival year.\n";
			ordinary = false;
		}
		if (isLeap == true && mod55 == 0) {
			cout << "This is bulukulu festival year.\n";
			ordinary = false;
		}
		if (ordinary == true) {
			cout << "This is an ordinary year.\n";
		}
	}

	cout.flush();
    return 0;
}

