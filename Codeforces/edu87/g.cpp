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
#include <random>
#include <chrono>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

mt19937 rnd((int)std::chrono::steady_clock::now().time_since_epoch().count());

int n, k;

int query(int a, int b, int sz) {
  cout << "? " << sz << " " << sz << endl;
  for (int i = 0; i < sz; i++) {
    cout << a + i;
    if (i + 1 < sz) {
      cout << ' ';
    } else {
      cout << endl;
    }
  }
  for (int i = 0; i < sz; i++) {
    cout << b + i;
    if (i + 1 < sz) {
      cout << ' ';
    } else {
      cout << endl;
    }
  }
  string ans; cin >> ans;
  if (ans == "FIRST") {
    return -1;
  } else if (ans == "SECOND") {
    return 1;
  } else if (ans == "EQUAL") {
    return 0;
  } else {
    assert(false);
    #define QAQ 42
    return QAQ;
  }
}

int main() {
  ios::sync_with_stdio(false);
  int T; cin >> T;
  while (T--) {
    cin >> n >> k;
    // step 1: whether 1 is valuable, with random
    bool isOne = false;
    uniform_int_distribution<int> dis(2, n);
    for (int i = 0; i < 20; i++) {
      int id = dis(rnd);
      int r = query(1, id, 1);
      if (r == 1) {
        isOne = true;
        break;
      }
    }
    if (isOne) {
      cout << "! 1" << endl;
      continue;
    }
    // step 2: binary lifting
    int sz = 1;
    while (sz + sz <= n) {
      int r = query(1, sz + 1, sz);
      assert(r <= 0);
      if (r == -1) {
        break;
      }
      sz += sz;
    }
    // step 3: ans is located at [sz + 1, min(sz + sz - 1, n)]
    int ans = sz + 1, l = 1, r = min(sz + sz, n) - sz - 1;
    while (l <= r) {
      int m = (l + r) / 2;
      int q = query(1, sz + 1, m);
      assert(q <= 0);
      if (q == 0) {
        ans = sz + m + 1;
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    cout << "! " << ans << endl;
  }
  return 0;
}