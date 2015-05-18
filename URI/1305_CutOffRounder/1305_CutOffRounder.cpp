#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	double num, cutOff, intPart, fracPart;
	const double epsilon = 0.00000000001;

	while (cin >> num >> cutOff) {
		fracPart = modf(num, &intPart);
		if (fracPart - cutOff > epsilon) {
			intPart += 1;
		}
		cout << static_cast<long long int>(intPart) << endl;
	}

    return 0;
}

