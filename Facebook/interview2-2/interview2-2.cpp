#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <list>

using namespace std;

typedef map<char, list<char> > Dictionary;

void translateMe(char *word, int ii, int size, Dictionary &dict);


void translateMe(char *word, int size, Dictionary &dict) {
	translateMe(word, 0, size, dict);
}

void translateMe(char *word, int ii, int size, Dictionary &dict) {
    for (; ii < size; ++ii) {
        Dictionary::iterator it = dict.find(word[ii]);
        if (it != dict.end()) {
            list<char> l = it->second;
			char backup = word[ii];
            for (list<char>::iterator it2 = l.begin(); it2 != l.end(); ++it2) {
				word[ii] = *it2;
                translateMe(word, ii + 1, size, dict);
            }
			word[ii] = backup;
			return;
        }
    }
    
    cout << word << endl;
}

int main() {
	Dictionary d;
	d['0'].push_back('O');
	d['1'].push_back('i'); d['1'].push_back('I');
	d['4'].push_back('a'); d['4'].push_back('A');
	d['5'].push_back('s'); d['5'].push_back('S');
	d['7'].push_back('T');
	d['9'].push_back('g');

	ostream_iterator<int> st(cout, " ");

	char word[] = "0h h4ppy p1e! 7ake 17 900d!";
	cout << word << endl << endl;

	translateMe(word, sizeof(word)/sizeof(char), d);

	return 0;
}
