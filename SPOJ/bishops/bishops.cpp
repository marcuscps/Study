#include <cstdio>

using namespace std;

#define MAXS	10^105

//=================================================================================================
int readValue(char *vec) {
	int ii = 0;
	char c;
	if (scanf("%c", &c) == 0) {
		return 0;
	};
	if (c == '0') {
		return 0;
	}
	while (c >= '0' && c <= '9') {
		vec[ii++] = c - '0';
		if (scanf("%c", &c) == 0) {
			break;
		}
	}
	vec[ii] = 0;
	return ii;
}

//=================================================================================================
void printValue(char *vec, int len) {
	for (int ii = 0; ii < len; ++ii) {
		printf("%c", (char)(vec[ii] + '0'));
	}
	printf("\n");
}

//=================================================================================================
char * multValue(char *vec, int *len, int mult) {
	int lenr = *len;

	int carry = 0;
	char val;
	for (--lenr; lenr >= 0; --lenr) {
		val = (vec[lenr] * mult) + carry;
		carry = val / 10;
		vec[lenr] = val % 10;
	}

	int lenInc = 0;
	while (carry) {
		++lenInc;
		--vec;
		*vec = carry % 10;
		carry = carry / 10;
	}

	*len = *len + lenInc;
	return vec;
}

//=================================================================================================
char * subValue(char *vec, int *len, int val) {
	int lenr = *len;
	--lenr;
	vec[lenr] -= val;

	while (vec[lenr] < 0 && lenr > 0) {
		vec[lenr] += 10;
		--lenr;
		--vec[lenr];
	}

	lenr = *len;
	while(vec[0] == 0) {
		++vec;
		--lenr;
	}
	*len = lenr;

	return vec;
}

//=================================================================================================
int main() {
	char vv[MAXS + 4];
	char *v;
	int len;

	while (1) {
		v = vv + 2;
		len = readValue(v);
		if (len == 0) {
			break;
		}

		if (len == 1 && v[0] == 1) {
			printf("1\n");
			continue;
		}

		v = multValue(v, &len, 2);
		v = subValue(v, &len, 2);
		printValue(v, len);
	}
	return 0;
}

