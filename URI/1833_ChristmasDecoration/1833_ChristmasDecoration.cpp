#include <iostream>
#include <cstdio>

#include <string>
#include <map>
#include <iomanip>
#include <algorithm>
#include <locale>
#include <vector>

#define USE_2_LINES
#define USE_VECTOR

using namespace std;

template <class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
    charT do_decimal_point() const { return sep; }
};

static const float removeCost = 0.5f;
static const float changeCost = 1.0f;
static const float addCost = 2.5f;

#ifdef USE_2_LINES
  static float v0[102], v1[102];

  inline void initEnv() {
  }

  inline void initDistance(size_t size) {
    float curCost = 0;
    for (size_t ii = 0; ii <= size; ++ii) {
      v0[ii] = curCost;
      curCost += addCost;
    }
  }

  float levenshteinDistance(const string& s, const string& t) {
    if (s == t) return 0;
    if (s.size() == 0) return t.size() * addCost;
    if (t.size() == 0) return s.size() * removeCost;

    initDistance(t.size());

    float* l0 = v0;
    float* l1 = v1;
    float curCost = removeCost;
    for (size_t ii = 0; ii < s.size(); ++ii, curCost += removeCost) {
      l1[0] = curCost;

      for (size_t jj = 0; jj < t.size(); ++jj) {
        float cost = (s[ii] == t[jj]) ? 0 : changeCost;
        l1[jj + 1] = min(l1[jj] + addCost, min(l0[jj + 1] + removeCost, l0[jj] + cost));
      }

      swap(l0, l1);
    }

    return l0[t.size()];
  }

#else
  static float m[102][102];

  inline void initEnv() {
    float *begin = m[0];
    float *last = begin + 102;
    float curCost = 0;
    while (begin != last) {
      *begin = curCost;
      curCost += addCost;
      ++begin;
    }
    
    curCost = removeCost;
    for (size_t ii = 1; ii < 101; ++ii) {
      m[ii][0] = curCost;
      curCost += removeCost;
    }
  }

  float levenshteinDistance(const string& s, const string& t) {
    if (s == t) return 0;
    if (s.size() == 0) return t.size() * addCost;
    if (t.size() == 0) return s.size() * removeCost;

    for (size_t ii = 0; ii < s.size(); ++ii) {
      for (size_t jj = 0; jj < t.size(); ++jj) {
        float cost = (s[ii] == t[jj]) ? 0 : changeCost;
        m[ii + 1][jj + 1] = min(m[ii + 1][jj] + addCost, min(m[ii][jj + 1] + removeCost, m[ii][jj] + cost));
      }
    }

    return m[s.size()][t.size()];
  }
#endif

#ifdef USE_VECTOR
  typedef vector<string> Dict;

  inline void initDict(Dict& dict) {
    dict.reserve(21);
  }

  inline char getColorCode(Dict& dict, string& color) {
    auto found = find(dict.begin(), dict.end(), color);
    size_t index;
    if (found != dict.end()) {
      index = distance(dict.begin(), found);
    } else {
      index = dict.size();
      dict.push_back(color);
    }

    return 'A' + index;
  }
#else
  typedef map<string, char> Dict;

  static char lastCode;

  inline void initDict(Dict& dict) {
    lastCode = '@'; // Last char before 'A'.
  }

  inline char getColorCode(Dict& dict, string& color) {
    auto found = dict.find(color);
    if (found != dict.end()) {
      return found->second;
    }

    char code = ++lastCode;
    dict[color] = code;
    return code;
  }
#endif

inline void readSequence(Dict& dict, string& sequence) {
  size_t size;
  cin >> size;
  sequence.clear();
  string color;
  while (size--) {
    cin >> color;
    char code = getColorCode(dict, color);
    sequence.push_back(code);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  std::cout.imbue(std::locale(std::cout.getloc(), new punct_facet<char, ','>));

  initEnv();

  string a(51, ' ');
  string b(51, ' ');

  size_t t;
  unsigned int r;

  cin >> t;
  for (size_t casen = 1; casen <= t; ++casen) {
    Dict dict;
    initDict(dict);

    cin >> r;
    readSequence(dict, a);
    readSequence(dict, b);

    cout << "Caso #" << casen << ": R$ " << fixed << setprecision(2) << (levenshteinDistance(a, b) * r) << endl;
  }

  return 0;
}
