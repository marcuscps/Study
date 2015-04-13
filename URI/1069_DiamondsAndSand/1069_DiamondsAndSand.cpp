#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t, openCounter, diamonds;
	string s;

	cin >> t;
	while (t--) {
		cin >> s;
		openCounter = diamonds = 0;
		for(char& c : s) {
			if (c == '<') ++openCounter;
			else if (c == '>' && openCounter > 0) { ++diamonds; --openCounter; }
		}
		cout << diamonds << endl;
	}

    return 0;
}

