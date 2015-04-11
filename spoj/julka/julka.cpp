#include <cstdio>

using namespace std;

#define MAXS	102

//=================================================================================================
int readValue(char *vec) {
	int ii = 0;
	char c;
	scanf("%c", &c);
	while (c >= '0' && c <= '9') {
		vec[ii++] = c - '0';
		c = getchar_unlocked();
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
char * div2Value(char *vec, int *len) {
	int l = *len;
	short int carry = 0;
	int a;
	int q;
	for (int ii = 0; ii < l; ++ii) {
		a = vec[ii] + carry;
		q = a / 2;
		if (q == 0 && a != 0) {
			carry = 10;
		} else {
			carry = (a % 2) * 10;
		}
		vec[ii] = (char)q;
	}
	while (*vec == 0) {
		++vec;
		--l;
	}

	*len = l;
	return vec;
}

//=================================================================================================
char * addValues(char *vec1, int len1, char *vec2, int len2, char *res, int *lenro) {
	int lenr = len1;
	if (len2 > lenr) lenr = len2;
	*lenro = lenr;

	int carry = 0;
	for (--len1, --len2; len1 >= 0 && len2 >= 0; --len1, --len2) {
		char rv = vec1[len1] + vec2[len2] + carry;
		res[--lenr] = rv % 10;
		carry = rv / 10;
	}

	for (; len1 >= 0; --len1) {
		char rv = vec1[len1] + carry;
		res[--lenr] = rv % 10;
		carry = rv / 10;
	}

	for (; len2 >= 0; --len2) {
		char rv = vec2[len2] + carry;
		res[--lenr] = rv % 10;
		carry = rv / 10;
	}

	if (carry) {
		*(--res) = carry;
		*lenro += 1;
	}

	return res;
}

//=================================================================================================
char * subValues(char *vec1, int len1, char *vec2, int len2, char *res, int *lenro) {
	int lenr = len1;
	if (len2 > lenr) lenr = len2;
	*lenro = lenr;

	int carry = 0;
	for (--len1, --len2; len1 >= 0 && len2 >= 0; --len1, --len2) {
		carry = vec1[len1] - vec2[len2] + carry;
		if (carry < 0) {
			res[--lenr] = 10 + carry;
			carry = -1;
		} else {
			res[--lenr] = carry;
			carry = 0;
		}
	}

	for (; len1 >= 0; --len1) {
		carry = vec1[len1] + carry;
		if (carry >= 0) {
			res[--lenr] = carry;
			carry = 0;
		} else {
			res[--lenr] = 10 + carry;
			carry = -1;
		}
	}

	for (; len2 >= 0; --len2) {
		carry = vec2[len2] + carry;
		if (carry >= 0) {
			res[--lenr] = carry;
			carry = 0;
		} else {
			res[--lenr] = 10 + carry;
			carry = -1;
		}
	}

	while (res[lenr] == 0 && *lenro > 1) {
		++res;
		(*lenro)--;
	}

	return res;
}

//=================================================================================================
int main() {
	char totalv[MAXS], difv[MAXS], julkav[MAXS], klaudiav[MAXS];
	char *total;
	char *julka;
	char *klaudia;
	int totaln, difn, julkan, klaudian;

	for (int t = 0; t < 10; ++t) {
		total = totalv + 2;
		julka = julkav + 2;
		klaudia = klaudiav + 2;
	
		totaln = readValue(total);
		difn   = readValue(difv);

		julka = addValues(total, totaln, difv, difn, julka, &julkan);
		julka = div2Value(julka, &julkan);
		printValue(julka, julkan);

		klaudia = subValues(total, totaln, julka, julkan, klaudia, &klaudian);
		printValue(klaudia, klaudian);
	}
	return 0;
}

