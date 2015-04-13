#include <cstdio>
#include <iostream>

using namespace std;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	int val;
	int ng, nm;
	int sg, sm;
	int ii;

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &ng, &nm);

		sg = 0;
		for (ii = 0; ii < ng; ++ii) {
			scanf("%d", &val);
			if (val > sg) {
				sg = val;
			}
		}

		sm = 0;
		for (ii = 0; ii < nm; ++ii) {
			scanf("%d", &val);
			if (val > sm) {
				sm = val;
			}
		}

		if (sg >= sm) {
			printf("Godzilla\n");
		} else if (sg < sm) {
			printf("MechaGodzilla\n");
		}
	}

	return 0;
}

