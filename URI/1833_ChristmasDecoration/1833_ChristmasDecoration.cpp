#include <iostream>
#include <cstdio>

#include <string>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <locale>

using namespace std;

//#define USE_LOCALES
#ifdef USE_LOCALES
template <class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
    charT do_decimal_point() const { return sep; }
};
#endif

unsigned int v0[102], v1[102];
static const unsigned int removeCost = 5;
static const unsigned int changeCost = 10;
static const unsigned int addCost = 25;

unsigned int levenshteinDistance(string& s, string& t) {
  if (s == t) return 0;
  if (s.size() == 0) return t.size() * addCost;
  if (t.size() == 0) return s.size() * removeCost;

  unsigned int* l0 = v0;
  unsigned int* l1 = v1;

  unsigned int curCost = 0;
  for (size_t ii = 0; ii <= t.size(); ++ii, curCost += addCost) {
    l0[ii] = curCost;
  }

  curCost = removeCost;
  for (size_t ii = 0; ii < s.size(); ++ii, curCost += removeCost) {
    l1[0] = curCost;

    for (size_t jj = 0; jj < t.size(); ++jj) {
      unsigned int cost = (s[ii] == t[jj]) ? 0 : changeCost;
      l1[jj + 1] = min(l1[jj] + addCost, min(l0[jj + 1] + removeCost, l0[jj] + cost));
    }

    swap(l0, l1);
  }

  return l0[t.size()];
}

inline char getColorCode(unordered_map<string, char>& dict, char &lastCode, string& color) {
  auto found = dict.find(color);
  if (found != dict.end()) {
    return found->second;
  }

  char code = ++lastCode;
  dict[color] = code;
  return code;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t, m, n;
  unsigned int r;
  string color;

#ifdef USE_LOCALES
  std::cout.imbue(std::locale(std::cout.getloc(), new punct_facet<char, ','>));
#endif

  cin >> t;
  for (size_t casen = 1; casen <= t; ++casen) {
    unordered_map<string, char> dict;
    char lastCode = ' ';
    string a, b;

    cin >> r >> m;
    for (size_t ii = 0; ii < m; ++ii) {
      cin >> color;
      char code = getColorCode(dict, lastCode, color);
      a.push_back(code);
    }

    cin >> n;
    for (size_t ii = 0; ii < n; ++ii) {
      cin >> color;
      char code = getColorCode(dict, lastCode, color);
      b.push_back(code);
    }
    
    auto units = levenshteinDistance(a, b);
    float cost = 1.0f * units * r / 10.0f;

#ifdef USE_LOCALES
    cout << "Caso #" << casen << ": R$ " << fixed << setprecision(2) << cost << endl;
#else
    float integer, decimal;
    decimal = modf(cost, &integer);
    decimal *= 100;

    cout << "Caso #" << casen << ": R$ " << static_cast<int>(integer) << "," << setfill('0') << setw(2) << decimal << endl;
#endif
  }

  return 0;
}

