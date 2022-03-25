#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int query(string s) {
  cout << s << endl;
  int x; cin >> x;
  if (x == 0 || x == -1) exit(0);
  return x;
}

int main() {
  int sa = 300 - query(string(300, 'a'));
  if (sa == 0) {
    int n = query("b") + 1;
    query(string(n, 'b'));
  }
  int n = sa + 300 - query(string(300, 'b'));
  if (n == sa) {
    query(string(n, 'a'));
  }

  string ans;
  for (int i = 0; i < n; i++) ans += 'a';
  int y = n - sa;

  for (int i = 0; i < n; i++) {
    ans[i] = 'b';
    if (i == n - 1) {
      assert(y == 1);
    }
    int r = query(ans);
    if (r < y) {
      assert(r + 1 == y);
      y = r;
    } else {
      assert(r == y + 1);
      ans[i] = 'a';
    }
  }
  assert(0);
  return 0;
}