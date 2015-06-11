#include <iostream>
#include <cstdio>
#include <unordered_map>

using namespace std;

typedef unordered_map<string, int> Substances;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	Substances substances;

	while (true) {
		size_t r;
		cin >> r;
		if (r == 0) break;

		substances.clear();
		string s3;
		int s3c;
		for (size_t ii = 0; ii < r; ++ii) {
			string s1, s2;
			cin >> s1;
			cin.ignore(3); // Ignore " + "
			cin >> s2;
			cin.ignore(3); // Ignore " -> "
			cin >> s3;

			Substances::iterator s3it = substances.find(s3);
			if (s3it == substances.end()) {
				Substances::iterator s1it = substances.find(s1);
				int s1c = (s1it == substances.end()) ? 0 : s1it->second;
				
				Substances::iterator s2it = substances.find(s2);
				int s2c = (s2it == substances.end()) ? 0 : s2it->second;
				
				s3c = min(max(s1c, s2c + 1), max(s1c + 1, s2c));
				substances[s3] = s3c;
			}
		}

		cout << s3 << " requires " << s3c << " containers\n";
	}
	cout.flush();

    return 0;
}

