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
  #define dbg(args...) cerr << #args << " -> ", err(args)
  void err() { std::cerr << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cerr << a << ' '; err(args...); }
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

int T, B;

int query(int x) {
  cout << x << endl;
  cin >> x; return x;
}

int main() {
  cin >> T >> B;
  while (T--) {
    vector<int> ans(B + 1);
    auto rev = [&ans](int l, int r) {
      for (int i = l; i <= r; i++) {
        swap(ans[i], ans[B - i + 1]);
      }
    };
    auto flip = [&ans](int l, int r) {
      for (int i = l; i <= r; i++) {
        ans[i] ^= 1; ans[B - i + 1] ^= 1;
      }
    };

    int type1 = 0, type2 = 0;
    for (int i = 1; i <= 5; i++) {
      ans[i] = query(i);
      ans[B - i + 1] = query(B - i + 1);
      if (!type1 && ans[i] == ans[B - i + 1]) {
        type1 = i;
      }
      if (!type2 && ans[i] != ans[B - i + 1]) {
        type2 = i;
      }
    }
    vector<PII> block = { { 1, 5 } }, op;
    for (int i = 6; i <= B / 2; i += 4) {
      int l = i, r = min(B / 2, i + 3);
      int r1 = -1, r2 = -1;
      if (type1) {
        r1 = query(type1);
      } else {
        query(1);
      }
      if (type2) {
        r2 = query(type2);
      } else {
        query(1);
      }
      op.emplace_back(r1, r2);
      for (int j = l; j <= r; j++) {
        ans[j] = query(j);
        ans[B - j + 1] = query(B - j + 1);
        if (!type1 && ans[j] == ans[B - j + 1]) {
          type1 = j;
        }
        if (!type2 && ans[j] != ans[B - j + 1]) {
          type2 = j;
        }
      }
      block.push_back({ l, r });
    }
    // dbg(T);
    assert(op.size() + 1 == block.size());
    for (int i = 0; i < (int)op.size(); i++) {
      int r1 = op[i].first, r2 = op[i].second;
      for (int j = i; j >= 0; j--) {
        int l = block[j].first, r = block[j].second;
        if (type1 <= r && type2 <= r && r1 != -1 && r2 != -1) {
          if (ans[type1] == r1 && ans[type2] == r2) {
            // keep
          } else if (ans[type1] == r1) {
            rev(l, r);
          } else if (ans[type2] == r2) {
            rev(l, r); flip(l, r);
          } else {
            flip(l, r);
          }
        } else if (type1 <= r && r1 != -1) {
          if (ans[type1] == r1) {
            // keep
          } else {
            flip(l, r);
          }
        } else if (type2 <= r && r2 != -1) {
          if (ans[type2] == r2) {
            // keep
          } else {
            flip(l, r);
          }
        }
      }
    }
    for (int i = 1; i <= B; i++) cout << ans[i];
    cout << endl;
    string verdict;
    cin >> verdict;
    if (verdict != "Y") {
      assert(false);
    }
  }
  return 0;
}