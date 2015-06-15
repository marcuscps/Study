#include <iostream>
#include <cstdio>
#include <unordered_map>

using namespace std;

typedef unordered_map<string, int> Dict;
typedef unsigned long long int Score;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	size_t m, n;
	Dict dict;
	string word;
	int weight;
	Score score;

	cin >> m >> n;

	while (m--) {
		cin >> word >> weight;
		dict[word] = weight;
	}

	while (n--) {
		score = 0;

		while ((cin >> word) && word[0] != '.') {
			Dict::const_iterator it = dict.find(word);
			if (it != dict.end()) {
				score += it->second;
			}
		}
		cout << score << "\n";
	}
	cout.flush();

    return 0;
}

