#include <iostream>
#include <string>
#include "stdlib.h"

using namespace std;

//int X[] = { 1, 3, 5, 7, 9, 1, 3, 5, 7, 9, 0, 2, 4, 6, 8, 0, 2, 4, 6, 8 };
int X[] = { 1, 9, 1, 9, 2, 8, 2, 8, 3, 7, 3, 7, 4, 6, 4, 6, 0, 5, 0, 5 };

void printGuide() {
	cout << "Index:   ";
	for (int ii = 0; ii < 10; ++ii) {
		cout << ii << " ";
	}
	for (int ii = 0; ii < 10; ++ii) {
		cout << ii << " ";
	}
	cout << endl;
}

void printX(string text, int m) {
	cout << text;
	for (int ii = 0; ii < 20; ++ii) {
		if (ii == m) { cout << "|"; }
		else { cout << " "; }
		cout << X[ii];
	}
	cout << endl;

}

int partition(int a, int b, int t) {
	int m = a - 1;
	for (int ii = a; ii < b; ++ii) {
		if (X[ii] < t) {
			++m;
			swap(X[m], X[ii]);
		}
	}
	return m;
}

int randInt(int l, int u) {
	return l + (rand() % (int)(u - l + 1));
}

void myQSort(int l, int u) {
	if (l < u) {
		int r = randInt(l, u);
		swap(X[l], X[r]);
		int t = X[l];
		int m = l;
		for (int ii = l + 1; ii <= u; ++ii) {
			if (X[ii] < t) {
				++m;
				swap(X[m], X[ii]);
			}
		}
		cout << "M: " << m << endl;
		swap(X[l], X[m]);
		printX("Out:    ", m);
		myQSort(l, m - 1);
		myQSort(m + 1, u);
	}
}

int main() {
	int p = 4;
	cout << "Partitioning around " << p << endl;
	printGuide();
	printX("Before: ", 20);
	int m1 = partition(0, 20, p);
	cout << "M: " << m1 << endl;
	printX("After:  ", 20);
	int m2 = partition(m1 + 1, 20, p + 1);
	cout << "M: " << m2 << endl;
	printX("After:  ", 20);

	cout << "-------------------" << endl;
	printGuide();
	printX("Before: ", 20);
	myQSort(0, 19);
	printX("Sorted: ", 20);
}

