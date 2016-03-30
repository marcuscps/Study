#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

typedef unsigned int uint;

struct Pilot {
  uint* scores[100];
  size_t index;

  Pilot() :
    index(0)
  {
  }

  inline void addScore(uint* score) {
    scores[index++] = score;
  }

  inline void clear() {
    index = 0;
  }

  inline uint getScore() {
    uint score = 0;
    for (size_t ii = 0; ii < index; ++ii) {
      score += *scores[ii];
    }
    return score;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t g; // 1 <= g <= 100
  size_t p; // 1 <= p <= 100
  size_t s; // 1 <= s <= 10
  size_t k; // 1 <= k <= p
  int val;
  Pilot pilots[101];
  uint winPoints[101] { 0 };
  uint winnerPoints;

  while (true) {
    cin >> g >> p;
    if (g == 0 && p == 0) break;

    for (size_t gg = 0; gg < g; ++gg) {
      for (size_t pp = 0; pp < p; ++pp) {
        cin >> val;
        pilots[pp].addScore(&winPoints[val - 1]);
      }
    }

    cin >> s;
    for (size_t ss = 0; ss < s; ++ss) {
      cin >> k;
      for (size_t kk = 0; kk < k; ++kk) {
        cin >> winPoints[kk];
      }

      winnerPoints = 0;
      set<size_t> winners;
      for (size_t pp = 1; pp <= p; ++pp) {
        uint points = pilots[pp - 1].getScore();
        if (points > winnerPoints) {
          winners.clear();
          winners.insert(pp);
          winnerPoints = points;
        } else if (points == winnerPoints) {
          winners.insert(pp);
        }
      }

      bool isFirst = true;
      for(auto const & pilotIndex : winners) {
        if (!isFirst) cout << " ";
        cout << pilotIndex;
        isFirst = false;
      }
      cout << endl;

      for (size_t kk = 0; kk < k; ++kk) {
        winPoints[kk] = 0;
      }
    }

    for (size_t pp = 0; pp < p; ++pp) {
      pilots[pp].clear();
    }
  }

  return 0;
}
