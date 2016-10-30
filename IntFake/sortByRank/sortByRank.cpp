#include <iostream>
#include <cstdio>
#include <iterator>
#include <vector>

/*
Input: An array of objects of a type that has a getRank() method. This method return 0, 1 or 2.
Sort the array based on the rank.

Example:
	Array: [a, b, c, d]

	a->GetRank() = 2
	b->GetRank() = 1
	c->GetRank() = 0
	d->GetRank() = 1

	So, c < a, c < b, etc...

	Result: [c, b, d, a]
*/

using namespace std;


class Object {
private:
	int rank;
public:
	Object(int rank) : rank(rank) { }
    int getRank() { return rank; }

	friend ostream & operator<<(ostream &o, const Object &rhs) {
		o << rhs.rank;
		return o;
	}
};


void sortByRank(vector<Object> &v) {
    int left = -1;
    int right = v.size();
    
    for (int ii = 0; ii < right; ) {
        int rank = v[ii].getRank();
        if (rank == 0) {
            swap(v[ii++], v[++left]);
        } else if (rank == 2) {
            swap(v[ii], v[--right]);
        } else {
            ++ii;
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	ostream_iterator<Object> printer(cout, " ");

	int t, n, rank;
	cin >> t;
	while (t--) {
		cin >> n;
		vector<Object> v;
		v.reserve(n);
		
		while (n--) {
			cin >> rank;
			v.push_back(Object(rank));
		}

		sortByRank(v);
		copy(v.begin(), v.end(), printer);
		cout << endl;
	}

    return 0;
}

