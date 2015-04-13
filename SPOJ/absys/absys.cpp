#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef unsigned int uint;

//=================================================================================================
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	uint t;
	char n1[100], n2[100], result[100];
	uint val1, val2;

	scanf("%u", &t);
	while (t--) {
		scanf("%s + %s = %s", n1, n2, result);
		if (strchr(n1, 'm') != NULL) {
			val1 = atoi(n2);
			val2 = atoi(result);
			printf("%u + %s = %s\n", val2 - val1, n2, result);
		} else if (strchr(n2, 'm') != NULL) {
			val1 = atoi(n1);
			val2 = atoi(result);
			printf("%s + %u = %s\n", n1, val2 - val1, result);
		} else {
			val1 = atoi(n1);
			val2 = atoi(n2);
			printf("%s + %s = %u\n", n1, n2, val1 + val2);
		}
	}

	return 0;
}

