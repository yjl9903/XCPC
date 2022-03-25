#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
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
const int maxn = 100000 + 5;

struct ACAM {
  static const int maxp = 500000 + 5;
  int ch[maxp][26], val[maxp], fail[maxp], sz;
  int match[maxp], fa[maxp];
  void clear() {
    // ms(fail, 0); ms(val, 0); ms(ch, 0);
    for (int i = 0; i <= sz; i++) {
      ms(ch[i], 0); fail[i] = fa[i] = 0;
    }
    sz = 1;
    for (int i = 0; i < 26; i++) ch[0][i] = 1;
  }
  ACAM() {
    clear();
  }
  void insert(char* s, int x) {
    int len = strlen(s), now = 1;
    for (int i = 0; i < len; i++) {
      int v = s[i] - 'a';
      if (!ch[now][v]) ch[now][v] = ++sz, fa[sz] =  now;
      now = ch[now][v];
    }
  }
  int siz[maxp], deg[maxp];
  vector<int> edge[maxp];
  void dfs(int u) {
    siz[u] = 1;
    for (int& v: edge[u]) {
      dfs(v); siz[u] += siz[v];
    }
  }
  void build() {
    queue<int> q; q.push(1);
    while (!q.empty()) {
      int t = q.front(); q.pop();
      for (int i = 0; i < 26; i++) {
        if (ch[t][i]) {
          fail[ch[t][i]] = ch[fail[t]][i];
          q.push(ch[t][i]);
        } else {
          ch[t][i] = ch[fail[t]][i];
        }
      }
    }
    for (int i = 0; i <= sz; i++) edge[i].clear();
    for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
    dfs(1);
    // for (int i = 1; i <= sz; i++) {
    //   siz[i] = 1; deg[fail[i]]++;
    // }
    // for (int i = 1; i <= sz; i++) if (!deg[i]) q.push(i);
    // while (!q.empty()) {
    //   int x = q.front(); q.pop();
    //   siz[fail[x]] += siz[x]; deg[fail[x]]--;
    //   if (deg[fail[x]] == 0) q.push(fail[x]);
    // }
    // for (int i = 0; i <= sz; i++) deg[i] = 0;
  }
  ll cal() {
    ll ans = 1ll * (sz - 1) * (sz - 1);
    for (int i = 1; i <= sz; i++) {
      if (fail[i] <= 1) continue;
      int x = i, y = fail[i];
      while (y > 1) y = fa[y], x = fa[x];
      ans -= siz[x] - 1;
    }
    return ans;
  }
} f;

int n;
char s[50];

int main() {
  while (scanf("%d", &n) == 1 && n) {
    f.clear();
    for (int i = 1; i <= n; i++) {
      scanf("%s", s); f.insert(s, i);
    }
    f.build();
    printf("%lld\n", f.cal());
  }
  return 0;
}