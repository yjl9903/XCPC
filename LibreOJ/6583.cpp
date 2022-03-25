#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const int maxn = 1000000 + 5;

int n, q, ch[maxn][26];
char s[maxn];

namespace sam {
  int sz, last, cnt[maxn << 1];
  int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
  void clear() {
    for (int i = 1; i <= sz; i++) {
      len[i] = link[i] = cnt[i] = 0;
      ms(ch[i], 0);
    }
    sz = last = 1;
  }
  int insert(int c, int last) {
    int cur = ++sz, p = last;
    len[cur] = len[last] + 1;
    cnt[cur] = 1;
    for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
    if (!p) link[cur] = 1;
    else {
      int q = ch[p][c];
      if (len[p] + 1 == len[q]) link[cur] = q;
      else {
        int nq = ++sz;
        len[nq] = len[p] + 1;
        link[nq] = link[q];
        link[q] = link[cur] = nq;
        memcpy(ch[nq], ch[q], sizeof ch[q]);
        for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
      }
    }
    return last = cur;
  }
  int c[maxn << 1], a[maxn << 1];
  void rsort() {
    for (int i = 1; i <= sz; i++) c[i] = 0;
    for (int i = 1; i <= sz; i++) c[len[i]]++;
    for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
    for (int i = 1; i <= sz; i++) a[c[len[i]]--] = i;
    for (int i = sz; i; i--) {
      int p = a[i];
      cnt[link[p]] += cnt[p];
    }
    // for (int i = 1; i <= sz; i++) dbg(i, cnt[i]);
  }
}

int pos[maxn];
void build() {
  queue<int> q; q.push(0);
  pos[0] = 1;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int c = 0; c < 26; c++) {
      if (!ch[u][c]) continue;
      int v = ch[u][c];
      pos[v] = sam::insert(c, pos[u]);
      q.push(v);
    }
  }
  sam::rsort();
}

int main() {
  sam::clear();
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    char s[2]; int fa;
    scanf("%s%d", s, &fa);
    ch[fa][s[0] - 'A'] = i;
  }
  build();
  while (q--) {
    scanf("%s", s);
    int m = strlen(s), u = 1;
    int flag = 1;
    reverse(s, s + m);
    for (int i = 0; i < m; i++) {
      int c = s[i] - 'A';
      if (sam::ch[u][c]) {
        u = sam::ch[u][c];
      } else {
        flag = 0; break;
      }
    }
    // dbg(u, flag);
    if (flag) printf("%d\n", sam::cnt[u]);
    else puts("0");
  }
  return 0;
}