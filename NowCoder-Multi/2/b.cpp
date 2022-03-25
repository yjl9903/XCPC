#include <iostream>
#include <cassert>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <set>
#include <deque>
using namespace std;
using PII = pair<int,int>;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

bool isDigit(char ch) {
  return '0' <= ch && ch <= '9';
}

using State = vector<PII>;

const int Epsilon = 0;

class Nfa : public vector<State> {
private:
  const string& pat;
  int cur = 0;

  int createState() {
    int root = size();
    push_back(State());
    return root;
  }

  PII parseAtom() {
    if (isDigit(pat[cur])) {
      int begin = createState();
      int end = createState();
      at(begin).emplace_back((int)pat[cur], end);
      cur++;
      return { begin, end };
    } else if (pat[cur] == '[') {
      cur++;
      int begin = createState();
      int end = createState();
      set<int> chs;
      while (cur < pat.length() && isDigit(pat[cur])) {
        chs.insert((int)pat[cur++]);
      }
      assert(pat[cur++] == ']');
      for (int ch: chs) at(begin).emplace_back(ch, end);
      return { begin, end };
    } else {
      assert(pat[cur++] == '(');
      auto node = parseAlt();
      assert(pat[cur++] == ')');
      return node;
    }
  }

  PII parseReg() {
    int begin = createState();
    int end = begin;
    auto peekPlus = [&]() {
      while (cur < pat.length() && pat[cur] == '+') cur++;
    };
    while (cur < pat.length() && (isDigit(pat[cur]) || pat[cur] == '[' || pat[cur] == '(')) {
      auto next = parseAtom();
      if (cur < pat.length() && pat[cur] == '+') {
        peekPlus();
        at(end).emplace_back(Epsilon, next.first);
        at(next.second).emplace_back(Epsilon, next.first);
        end = next.second;
      } else {
        at(end).emplace_back(Epsilon, next.first);
        end = next.second;
      }
    }
    return { begin, end };
  }

  PII parseAlt() {
    int begin = createState();
    auto next = parseReg();
    at(begin).emplace_back(Epsilon, next.first);
    vector<int> subEnd { next.second };
    while (cur < pat.length() && pat[cur] == '|') {
      cur++;
      auto next = parseReg();
      at(begin).emplace_back(Epsilon, next.first);
      subEnd.push_back(next.second);
    }
    int end = createState();
    for (auto& state: subEnd) {
      at(state).emplace_back(Epsilon, end);
    }
    return { begin, end };
  }

public:
  Nfa(const string& pat): pat(pat) {
    parseAlt();
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string pat, str;
  cin >> pat >> str;

  Nfa nfa { pat };
  int nSz = nfa.size();
  int m = str.length();
  auto dis = vector<vector<int>>(nSz, vector<int>(m + 1, inf));
  deque<PII> dq;
  dis[0][0] = 0;
  dq.emplace_back(0, 0);

  while (!dq.empty()) {
    auto cur = dq.front();
    int cdis = dis[cur.first][cur.second];
    dq.pop_front();
    auto relaxFront = [&](int u, int l) {
      if (dis[u][l] > cdis) {
        dis[u][l] = cdis;
        dq.emplace_front(u, l);
      }
    };
    auto relaxBack = [&](int u, int l) {
      if (dis[u][l] > cdis + 1) {
        dis[u][l] = cdis + 1;
        dq.emplace_back(u, l);
      }
    };
    if (cur.second < m) {
      // delete
      relaxBack(cur.first, cur.second + 1);
    }
    for (auto& [ch, next]: nfa[cur.first]) {
      if (ch == Epsilon) {
        relaxFront(next, cur.second);
      } else {
        if (cur.second < m) {
          if (ch == str[cur.second]) {
            // match
            relaxFront(next, cur.second + 1);
          } else {
            // change
            relaxBack(next, cur.second + 1);
          }
        }
        // insert
        relaxBack(next, cur.second);
      }
    }
  }
  printf("%d\n", dis[nSz - 1][m]);
  return 0;
}