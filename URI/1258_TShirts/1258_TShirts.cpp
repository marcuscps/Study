#include <iostream>
#include <cstdio>

#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

using namespace std;

struct Item {
  string name;
  char detailColor;
  int size;

  char getSizeAsChar() const {
    return ((size == 0) ? 'P' : ((size == 1) ? 'M' : 'G'));
  }

  friend ostream &operator<<(ostream& os, const Item& info) {
    os << ((info.detailColor == 'b') ? "branco" : "vermelho") << " " << info.getSizeAsChar() << " " << info.name;
    return os;
  }

  friend istream &operator>>(istream& is, Item& info) {
    string color;
    char size;
    std::getline(is, info.name);
    is >> color >> size;
    cin.ignore(1);
    info.detailColor = (color == "branco") ? 'b' : 'v';
    info.size = (size == 'P') ? 0 : ((size == 'M') ? 1 : 2);
    return is;
  }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool printLine = false;

    while (true) {
      size_t n;
      cin >> n;
      if (n == 0) break;
      cin.ignore(1);

      if (printLine) cout << endl;

      std::vector<Item *> items;
      items.reserve(n);
      while (n--) {
        Item *newItem = new Item();
        cin >> *newItem;
        items.push_back(newItem);
      }

      std::sort(items.begin(), items.end(), [](const Item* lhs, const Item* rhs) {
        if (lhs->detailColor != rhs->detailColor) return lhs->detailColor < rhs->detailColor;
        if (lhs->size < rhs->size) return true;
        if (lhs->size > rhs->size) return false;
        return lhs->name < rhs->name;
      });
      
      std::for_each(items.cbegin(), items.cend(), [](const Item* item) { cout << *item << endl; });
      std::for_each(items.begin(), items.end(), std::default_delete<Item>());

      printLine = true;
    }

    return 0;
}

