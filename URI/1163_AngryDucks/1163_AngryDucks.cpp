#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>

#define PI	3.14159
#define G	9.80665

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	double h, p1, p2;
	int n;
	double a, v;

	double d, vy, vx;
	while (std::cin >> h >> p1 >> p2 >> n) {
		while (n--) {
			std::cin >> a >> v;

			a = (a * PI) / 180.00;
			vy = sin(a) * v;
			vx = cos(a) * v;
			d = ((vx * vy) + (vx * sqrt((vy * vy) + (2.00 * G * h)))) / G;

			std::cout << std::fixed << std::setprecision(5) << d << " -> " << ((d >= p1 && d <= p2) ? "DUCK" : "NUCK") << "\n";
		}
	}
	std::cout.flush();

    return 0;
}

