#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

typedef queue<int> Cards;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	Cards cards;

	while (true) {
		int n;
		cin >> n;
		if (n == 0) break;

		if (n == 1) {
			cout << "Discarded cards:\n";
			cout << "Remaining card: 1\n";
			continue;
		}

		for (int ii = 3; ii <= n; ++ii) {
			cards.push(ii);
		}
		cards.push(2);

		cout << "Discarded cards: 1";
		while (cards.size() > 1) {
			cout << ", " << cards.front();
			cards.pop();

			cards.push(cards.front());
			cards.pop();
		}
		cout << "\n";
		cout << "Remaining card: " << cards.front() << "\n";
		cards.pop();
	}
	cout.flush();

    return 0;
}

