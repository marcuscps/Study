#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int n, a, b, ageb, age;
	int vs[2000], r[2000];

	scanf("%d", &n);
	for (a = 0; a < n; ++a) {
		scanf("%d", &vs[a]);
	}

	for (b = 0; b < n; ++b) {
		r[b] = vs[b] * n;
		ageb = n - b;
		for (a = b - 1; a >= 0; --a) {
			age = ageb + a;
			r[a] = max((age * vs[a]) + r[a + 1], (age * vs[b]) + r[a]);
		}
	}

	printf("%d\n", r[0]);
	
	return 0;
}
