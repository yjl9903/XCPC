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
#include <queue>
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
const int maxn = 1000000 + 5;

namespace acam {
  static const int maxp = 1000000 + 5;
  static const int S = 26;
  static const int Base = 'a';
  int sz, ch[maxp][S], fail[maxp], val[maxp];
  int node() {
    ms(ch[++sz], 0);
    fail[sz] = val[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(char* s, int i) {
    int u = 1, len = 0;
    for (int i = 0; s[i]; i++, len++) {
      int v = s[i] - Base; // !
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
    }
    val[u] = len;
    return u;
  }
  int link[maxp];
  vector<int> edge[maxp];
  void build() {
    queue<int> q; q.push(1);
    while (!q.empty()) {
      int t = q.front(); q.pop();
      for (int i = 0; i < S; i++) {
        if (ch[t][i]) {
          fail[ch[t][i]] = ch[fail[t]][i];
          q.push(ch[t][i]);
        } else {
          ch[t][i] = ch[fail[t]][i];
        }
      }
    }
    for (int i = 2; i <= sz; i++) {
      edge[fail[i]].push_back(i);
    }
    function<void(int,int)> dfs = [&](int u, int last) {
      link[u] = last;
      if (val[u] > 0) last = u;
      for (int v: edge[u]) {
        dfs(v, last);
      }
    };
    dfs(1, 0);
  }
}

char a[5005], s[maxn];
int n, m, fail[maxn], fail2[maxn], ok[5005];

int main() {
  acam::clear();
  scanf("%s%d", a + 1, &n);

  m = strlen(a + 1);
  for (int i = 2; i <= m; i++) {
    int cur = fail[i - 1];
    while (cur && a[cur + 1] != a[i]) cur = fail[cur];
    if (a[cur + 1] == a[i]) cur++;
    fail[i] = cur;
  }
  int L = m;
  while (L) {
    if (m % (m - fail[L]) == 0) {
      m = m - fail[L];
      break;
    }
    L = fail[L];
  }
  for (int i = m + 1; i <= m + m + m + m; i++) a[i] = a[i - m];
  
  bool isOne = false;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    if (len <= m) {
      acam::insert(s + 1, i);
      continue;
    }
    int isA = -1;
    for (int i = 1, cur = 0; i <= len; i++) {
      while (cur > 0 && s[i] != a[cur + 1]) cur = fail[cur];
      if (a[cur + 1] == s[i]) cur++;
      if (cur == m) {
        isA = i - m + 1;
        break;
      }
    }
    if (isA != -1) {
      for (int i = 2; i <= len; i++) {
        int cur = fail2[i - 1];
        while (cur > 0 && s[cur + 1] != s[i]) cur = fail2[cur];
        if (s[cur + 1] == s[i]) cur++;
        fail2[i] = cur;
      }
      int x = len; bool ok = false;
      while (x) {
        if (len - x == m) {
          ok = true; break;
        }
        x = fail2[x];
      }
      if (ok) {
        string tot;
        int i = 1;
        while (i < isA) tot += s[i++];
        while (i + m - 1 <= len) i += m;
        while (i <= len) tot += s[i++];
        for (int i = 0; i < (int)tot.size(); i++) s[i] = tot[i];
        s[tot.size()] = 0;
        if (tot.empty()) {
          isOne = true;
        } else {
          acam::insert(s, i);
        }
      }
    }
  }
  if (isOne) {
    puts("1"); return 0;
  }
  
  acam::build();
  int ans = inf;
  for (int st = 1; st <= m; st++) {
    ok[st - 1] = 0;
    int u = 1;
    for (int i = st; i <= st + m + m + m - 1; i++) {
      ok[i] = inf;
      u = acam::ch[u][a[i] - 'a'];
      int x = u;
      while (x) {
        int pos = i - acam::val[x];
        if (pos < i && ok[pos] < inf) {
          ok[i] = min(ok[i], 1 + ok[pos]);
        }
        x = acam::link[x];
      }
      if (i == st + m - 1
       || i == st + m + m - 1
       || i == st + m + m + m - 1) {
        ans = min(ans, ok[i]);
      }
    }
  }
  if (ans == inf) puts("-1");
  else printf("%d\n", ans);
  return 0;
}