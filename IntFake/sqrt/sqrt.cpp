#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

double mySqrt(double v) {
	if (v == 0.0) return 0.0f;

    double l = 0.0f;
    double r = 1.0f;
    if (v > 1.0) {
        r = v;
    }


    while(true) {
        double m = (l + r) / 2.0f;
        double q = (v / m);
        double diff = m - q;
        if (diff > -0.00005 && diff < 0.00005) {
            return m;
        } else if (q > m) {
            l = m;
        } else {
            r = m;
        }
    }        
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t;
	double v;

	cin >> t;
	while (t--) {
		cin >> v;
		cout << fixed << setprecision(4) << mySqrt(v) << endl;
	}

    return 0;
}
