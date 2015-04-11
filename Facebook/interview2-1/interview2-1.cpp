#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;


void pivot( int *v, int size ) {
	int lp = -1, rp = size;
	for (int ii = 0; ii < rp; ) {
		if (v[ii] == 0) {
			swap(v[++lp], v[ii]);
			if (ii == lp) ++ii;
		} else if (v[ii] == 2) {
			swap(v[--rp], v[ii]);
		} else {
			++ii;
		}
	}
}

#define test(V)	\
	{	int s = sizeof(V)/sizeof(int); \
		pivot(V, s); \
		copy(V, V + s, st); \
		cout << endl;\
	}

int main() {
	ostream_iterator<int> st(cout, " ");

	{ int v[] = { 0, 0, 0, 1, 1, 1, 2, 2, 2 }; test(v); }
	{ int v[] = { 2, 2, 2, 1, 1, 1, 0, 0, 0 }; test(v); }
	{ int v[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2 }; test(v); }
	{ int v[] = { 2, 1, 0, 2, 1, 0, 2, 1, 0 }; test(v); }
	{ int v[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; test(v); }
	{ int v[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 }; test(v); }
	{ int v[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 }; test(v); }
	{ int v[] = { 2, 1, 2, 2, 2, 2, 2, 2, 2 }; test(v); }
	{ int v[] = { 0, 2, 1, 2, 2, 2, 2, 2, 2 }; test(v); }
	{ int v[] = { 0, 2, 1, 2, 2, 2, 2, 1, 0 }; test(v); }
	{ int v[] = {}; test(v); }

	return 0;
}
