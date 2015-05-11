#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Item {
	size_t index;
	size_t grade;

	Item() : index(0), grade(0) { }

	void set(size_t indexV, size_t gradeV) {
		index = indexV;
		grade = gradeV;
	}
};

struct ItemSorter {
    inline bool operator() (const Item& a, const Item& b) {
        return (a.grade > b.grade);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	size_t t, n, grade, outOfOrder;
	Item items[1000];

	cin >> t;
	while (t--) {
		cin >> n;
		for (size_t ii = 0; ii < n; ++ii) {
			cin >> grade;
			items[ii].set(ii, grade);
		}

		std::sort(items, items + n, ItemSorter());

		outOfOrder = n;
		for (size_t ii = 0; ii < n; ++ii) {
			if (ii != items[ii].index) {
				--outOfOrder;
			}
		}

		cout << outOfOrder << endl;
	}

    return 0;
}

