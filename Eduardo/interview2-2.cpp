#include <iostream>
#include <string>

using namespace std;

int find_paths( int **mat, int n, int m) {
    for (int ii = n - 1; ii >= 0; --ii) {
        for (int jj = m - 1; jj >= 0; --jj) {
            if (mat[ii][jj] != -1) {
                if (ii > 0 && mat[ii - 1][jj] != -1) {
                    mat[ii - 1][jj] += mat[ii][jj];
                }
                if (jj > 0 && mat[ii][jj - 1] != -1) {
                    mat[ii][jj - 1] += mat[ii][jj];
                }
            }
        }
    }
    return mat[0][0];
}

int main() {
	int **t1 = new int*[3];
	for (int ii = 0; ii < 3; ++ii) {
		t1[ii] = new int[3];
		for (int jj = 0; jj < 3; ++jj)
			t1[ii][jj] = 0;
	}

	cout << "T1 -> " << find_paths( t1, 3, 3 ) << "  <==>  6" << endl;

	t1[1][1] = -1;
	cout << "T2 -> " << find_paths( t1, 3, 3 ) << "  <==>  2" << endl;
	
	return 0;
}

