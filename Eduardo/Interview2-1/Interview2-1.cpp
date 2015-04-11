#include <iostream>
#include <cstdio>
#include <string>

#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

void inc_index(string &s, int &p);
void dec_index(string &s, int &p);
bool is_valid(char c);
char convert(char c);

bool is_palindrome(string s) {
	cout << "TESTING: " << s << endl;
    if (s.size() == 0) return true;
    
    int ii, ee;
    ii = 0;
    ee = s.size() - 1;
    
    if (is_valid(s[ii]) == false) inc_index(s, ii);
    if (is_valid(s[ee]) == false) dec_index(s, ii);
    
    while (ii < ee) {
        char ca = convert(s[ii]);
        char ce = convert(s[ee]);
        
        if (ca != ce) return false;

		cout << "  " << ca << " (" << ii << ") == " << ce << "(" << ee << ")";
        inc_index(s, ii);
        dec_index(s, ee);
		cout << "  -->  " << ii << ", " << ee << endl;
    }

    return true;
}

void inc_index(string &s, int &p) {
	do {
        ++p;
	} while (p < s.size() && is_valid(s[p]) == false);
}

void dec_index(string &s, int &p) {
	do {
        --p;
	} while (p >= 0 && is_valid(s[p]) == false);
}

bool is_valid(char c) {
    if (c >= 'a' && c <= 'z') return true;
    if (c >= 'A' && c <= 'Z') return true;
    return false;
}

char convert(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cout << "Empty --> " << is_palindrome("") << "  <==>  " << true << endl;
	cout << "\"a\" --> " << is_palindrome("a") << "  <==>  " << true << endl;
	cout << "\"aa\" --> " << is_palindrome("aa") << "  <==>  " << true << endl;
	cout << "\"aaa\" --> " << is_palindrome("aaa") << "  <==>  " << true << endl;
	cout << "\"aba\" --> " << is_palindrome("aba") << "  <==>  " << true << endl;
	cout << "\"abba\" --> " << is_palindrome("abba") << "  <==>  " << true << endl;
	cout << "\"abcba\" --> " << is_palindrome("abcba") << "  <==>  " << true << endl;
	cout << "\"1a2a3A\" --> " << is_palindrome("1a2a3A") << "  <==>  " << true << endl;
	cout << "\"1a@b!A\" --> " << is_palindrome("1a@b!A") << "  <==>  " << true << endl;
	cout << "\"!@#232a4b34122343A\" --> " << is_palindrome("!@#232a4b34122343A") << "  <==>  " << true << endl;
	cout << "\"!@#232a4b34122343B\" --> " << is_palindrome("!@#232a4b34122343B") << "  <==>  " << false << endl;

	return 0;
}

