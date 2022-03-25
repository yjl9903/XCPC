#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <deque>
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
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
 
  PII parseReg() {
    int begin = createState();
    int end = begin;
    while (cur < pat.length()) {
      auto peekPlus = [&]() {
        while (cur < pat.length() && pat[cur] == '+') cur++;
      };
      if (isDigit(pat[cur])) {
        int nE = createState();
        at(end).emplace_back(Epsilon, nE);
        end = nE;

        int next = createState();
        at(end).emplace_back((int)pat[cur], next);
        cur++;
        if (cur < pat.length() && pat[cur] == '+') {
          peekPlus();
          at(next).emplace_back(Epsilon, end);
        }
        end = next;
      } else if (pat[cur] == '[') {
        cur++;
        int nE = createState();
        at(end).emplace_back(Epsilon, nE);
        end = nE;

        int next = createState();
        while (cur < pat.length() && isDigit(pat[cur])) {
          at(end).emplace_back((int)pat[cur], next);
          cur++;
        }
        assert(pat[cur++] == ']');
        if (cur < pat.length() && pat[cur] == '+') {
          peekPlus();
          at(next).emplace_back(Epsilon, end);
        }
        end = next;
      } else if (pat[cur] == '(') {
        cur++;
        auto next = parseAlt();
        at(end).emplace_back(Epsilon, next.first);
        assert(pat[cur++] == ')');
        if (cur < pat.length() && pat[cur] == '+') {
          peekPlus();
          at(next.second).emplace_back(Epsilon, next.first);
        }
        end = next.second;
      } else {
        break;
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
    dbg(cur.first, cur.second, cdis);
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