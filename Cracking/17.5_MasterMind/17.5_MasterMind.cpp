#include <iostream>
#include <cstdio>

using namespace std;

class MasterMind {
private:
	static const int SIZE = 4;

	static int index(char c) {
		switch (c) {
			case 'R':	return 0;
			case 'G':	return 1;
			case 'B':	return 2;
			case 'Y':	return 3;
			default:	return SIZE;
		}
		return SIZE;
	}

public:
	static pair<int, int> match(string value, string guess) {
		if (value.size() != guess.size() || value.size() != SIZE) {
			return make_pair(-1, -1);
		}

		int freqsValue[SIZE + 1] = {0};
		int freqsGuess[SIZE + 1] = {0};

		int hits = 0;
		int pseudo = 0;
		for (size_t ii = 0; ii < SIZE; ++ii) {
			if (value[ii] == guess[ii]) {
				++hits;
			} else {
				++freqsValue[index(value[ii])];
				++freqsGuess[index(guess[ii])];
			}
		}

		if (hits < SIZE) {
			for (int ii = 0; ii < SIZE; ++ii) {
				pseudo += min(freqsValue[ii], freqsGuess[ii]);
			}
		}

		return make_pair(hits, pseudo);
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t = 0;
	cin >> t;
	while (t--) {
		string value, guess;
		cin >> value >> guess;
		auto res = MasterMind::match(value, guess);
		cout << res.first << " " << res.second << endl;
	}

    return 0;
}

