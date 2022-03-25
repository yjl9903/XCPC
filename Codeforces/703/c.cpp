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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int query(int L, int R) {
  cout << "? " << L << " " << R << endl;
  cin >> L;
  return L;
}

int main() {
  int n;
  cin >> n;
  int key = query(1, n);
  int ans = -1;
  if (key > 1 && query(1, key) == key) {
    ans = 1;
    int l = 1, r = key - 1;
    while (l <= r) {
      int m = (l + r) / 2;
      if (m + 1 < key && query(m + 1, key) == key) {
        ans = m + 1;
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
  } else {
    ans = n;
    int l = key + 1, r = n;
    while (l <= r) {
      int m = (l + r) / 2;
      if (key < m && query(key, m) == key) {
        ans = m;
        r = m - 1;
      } else {
        l = m + 1;
      }
    }
  }
  assert(ans != -1);
  cout << "! " << ans << endl;
  return 0;
}