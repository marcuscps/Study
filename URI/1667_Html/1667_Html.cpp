#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	string hr(80, '-');
	
	string word;
	size_t length = 0;
	bool needSpace = false;
	while (cin >> word) {
		if (word[0] == '<') {
			if (word == "<br>") {
				cout << "\n";
				length = 0;
				needSpace = false;
			} else if (word == "<hr>") {
				if (length > 0) cout << "\n";
				cout << hr << "\n";
				length = 0;
				needSpace = false;
			}
			
			continue;
		}

		if (needSpace) length += 1;
		if (length + word.size() >= 80) {
			cout << "\n";
			length = 0;
			needSpace = false;
		}
		if (needSpace) cout << " ";

		cout << word;
		needSpace = true;
		length += word.size();
	}
	
	if (length > 0) cout << "\n";
	cout.flush();

    return 0;
}

