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
#include <ctime>
#include <random>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000 + 5;

mt19937 rnd(time(0));

int n, m, k;
char tmp[maxn];
string s[maxn];

void print(vector<int> v) {
  for (int i = 0; i < 8; i++) cout << v[i] << ' ';
  cout << endl;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  if (k >= 7) {
    printf("%d\n", n * (n - 1) / 2);
    return 0;
  }

  getchar();
  for (int i = 1; i <= n; i++) {
    gets(tmp);
    s[i] = string(tmp);
  }

  vector<vector<int> > states;
  function<void(int,vector<int>)> dfs = [&](int x, vector<int> pre) {
    if (x == 8) {
      states.push_back(pre);
      return ;
    }
    for (int i = 0; i < x; i++) {
      if (i == pre[i]) {
        vector<int> v(pre);
        v[x] = i;
        dfs(x + 1, v);
      }
    }
    pre[x] = x;
    dfs(x + 1, pre);
  };
  dfs(1, vector<int>(8, 0));

  vector<vector<int> > v;
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      vector<int> pre(8);
      for (int i = 0; i < 8; i++) pre[i] = i;
      function<int(int)> find = [&](int x) {
        return x == pre[x] ? x : pre[x] = find(pre[x]);
      };
      for (int k = 0; k < m; k++) {
        int a = find(s[i][k] - 'a'), b = find(s[j][k] - 'a');
        if (a != b) {
          pre[a] = b;
        }
      }
      for (int i = 0; i < 8; i++) pre[i] = find(i);
      vector<int> res(8);
      int cnt = 0;
      for (int i = 0; i < 8; i++) {
        if (i != pre[i]) continue;
        int mn = i;
        for (int j = 0; j < 8; j++) {
          if (pre[j] == i) mn = min(i, j), cnt++;
        }
        cnt--;
        for (int j = 0; j < 8; j++) {
          if (pre[j] == i) res[j] = mn;
        }
      }
      if (cnt <= k) v.push_back(res);
    }
  }

  shuffle(begin(v), end(v), rnd);

  int ans = 0;
  for (auto& x: states) {
    int cost = 0;
    vector<int> siz(8, 0);
    for (int i = 0; i < 8; i++) siz[x[i]]++;
    for (int i = 0; i < 8; i++) if (siz[i]) cost += siz[i] - 1;
    if (cost != k) continue;
    int cnt = 0;
    vector<int> p(8, -1);
    for (auto& st: v) {
      for (int i = 0; i < 8; i++) p[i] = -1;
      int flag = 1;
      for (int i = 0; i < 8; i++) {
        if (p[st[i]] == -1) {
          p[st[i]] = x[i];
        } else {
          if (p[st[i]] != x[i]) {
            flag = 0; break;
          }
        }
      }
      if (flag) cnt++;
    }
    ans = max(ans, cnt);
    if (ans == n * (n - 1) / 2) break;
  }
  cout << ans << '\n';

  return 0;
}