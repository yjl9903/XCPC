#include <iostream>
#include <sstream>
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
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, sz, root[maxn];
int ls[maxn * 40], rs[maxn * 40], cnt[maxn * 40];
char buf[maxn * 100];

void update(int i, int x, int pre, int l, int r, int& rt) {
  rt = ++sz;
  ls[rt] = ls[pre];
  rs[rt] = rs[pre];
  cnt[rt] = cnt[pre] + x;
  if (l == r) return ;
  int m = (l + r) / 2;
  if (i <= m) update(i, x, ls[pre], lson);
  else update(i, x, rs[pre], rson);
}
int query(int i, int l, int r, int rt) {
  if (!rt) return 0;
  if (l == r) return cnt[rt];
  int m = (l + r) / 2;
  if (i <= m) return cnt[rs[rt]] + query(i, lson);
  else return query(i, rson);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n;
  cin.ignore();
  for (int i = 1; i <= n; i++) {
    cin.getline(buf, maxn * 100 - 1);
    stringstream ss(buf);
    string str;
    int pre = root[i - 1];
    root[i] = pre;
    while (ss >> str) {
      int id = atoi(str.substr(1).c_str());
      if (str[0] == '+') {
        update(id, 1, pre, 0, n, root[i]);
      } else {
        update(id, -1, pre, 0, n, root[i]);
      }
      pre = root[i];
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int d;
    cin >> d;
    // cout << ans << " " << d << " -> " << query(ans, 0, n, root[d]) << endl;
    ans = (ans + query(ans, 0, n, root[d])) % n;
  }
  cout << ans << endl;
  return 0;
}