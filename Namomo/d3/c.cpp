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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
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

int n, q;
char buf[maxn];

int main() {
  scanf("%d", &n);
  int cnt = n, siz = n / 5, dfn = 0;
  map<string, PII> mp;
  map<PII, string> ord;
  set<PII> key;
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%s%d", buf, &x);
    mp[buf] = { x, ++dfn };
    ord[mp[buf]] = buf;
  }
  for (auto it = ord.rbegin(); it != ord.rend() && key.size() < siz; it++) {
    key.insert(it->first);
  }
  auto getNext = [&](PII cur) {
    auto it = ord.lower_bound(cur);
    assert(it != ord.begin());
    it--;
    return it->first;
  };
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    // dbg(i);
    char op[4];
    scanf("%s%s", op, buf);
    vector<pair<string,int> > evs;
    if (op[0] == '-') {
      auto val = mp[buf];
      cnt--;
      mp.erase(buf);
      ord.erase(val);
      if (key.count(val)) {
        if (cnt / 5 < key.size()) {
          key.erase(val);
        } else {
          PII nxt = getNext(*key.begin());
          key.erase(val);
          key.insert(nxt);
          evs.emplace_back(ord[nxt], 1);
        }
      } else {
        if (cnt / 5 < key.size()) {
          assert(!key.empty());
          evs.emplace_back(ord[*key.begin()], 0);
          key.erase(key.begin());
        }
      }
    } else if (op[0] == '+') {
      int x;
      scanf("%d", &x);
      PII val { x, ++dfn };
      cnt++;
      mp[buf] = val;
      ord[val] = buf;
      if (cnt / 5 > key.size()) {
        if (key.empty()) {
          PII nxt = ord.rbegin()->first;
          key.insert(nxt);
          evs.emplace_back(ord[nxt], 1);
        } else if (val > *key.begin()) {
          key.insert(val);
          evs.emplace_back(buf, 1);
        } else {
          PII nxt = getNext(*key.begin());
          key.insert(nxt);
          evs.emplace_back(ord[nxt], 1);
        }
      } else {
        // dbg(val > *key.begin());
        if (!key.empty() && val > *key.begin()) {
          evs.emplace_back(buf, 1);
          evs.emplace_back(ord[*key.begin()], 0);
          key.erase(key.begin());
          key.insert(val);
        }
      }
      if (!key.count(val)) {
        evs.insert(evs.begin(), { buf, 0 });
      }
    }
    // sort(evs.begin(), evs.end());
    for (auto& x: evs) {
      printf("%s", x.first.c_str());
      if (x.second) {
        puts(" is working hard now.");
      } else {
        puts(" is not working now.");
      }
    }
  }
  return 0;
}