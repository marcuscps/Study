#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef map<char, vector<char> > Dict;


void get_trans_aux(string &s, int i, Dict dic, vector<string> &r);

vector<string> get_trans(string s, Dict dic) {
    vector<string> v;
    get_trans_aux(s, 0, dic, v);
    return v;
}

void get_trans_aux(string &s, int i, Dict dic, vector<string> &r) {
    if (i == s.size()) {
        r.push_back(s);
        return;
    }
  
  get_trans_aux(s, i + 1, dic, r);

  auto p = dic.find(s[i]);
  if (p != dic.end()) {
	  char c = s[i];
	  auto v = p->second;
	  for(auto ii = v.begin(); ii != v.end(); ++ii) {
		  s[i] = *ii;
		  get_trans_aux(s, i + 1, dic, r);
	  }
	  s[i] = c;
  }
}

int main() {
	Dict d1;
	vector<char> d1a;
	d1a.push_back('A');
	d1a.push_back('*');
	d1['a'] = d1a;
	vector<char> d1c;
	d1c.push_back('C');
	d1c.push_back('<');
	d1['c'] = d1c;

	vector<string> r1 = get_trans("abc", d1);
	cout << "abc:" << endl;
	for (auto ii = r1.begin(); ii != r1.end(); ++ii) {
		cout << "  " << *ii << endl;
	}

	vector<string> r2 = get_trans("abcab", d1);
	cout << "abcab:" << endl;
	for (auto ii = r2.begin(); ii != r2.end(); ++ii) {
		cout << "  " << *ii << endl;
	}

	return 0;
}

