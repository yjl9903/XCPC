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
const int maxn = 2000000 + 5;

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
  int insert(int c) {
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
    // for (int i = sz; i; i--) {
    //   int p = a[i];
    //   cnt[link[p]] += cnt[p];
    // }
  }
}
using sam::ch;
using sam::link;

int n, fail[maxn], ans[maxn << 1], dep[maxn << 2];
char s[maxn];
vector<string> bag[maxn];

string prework(char s[]) {
  int n = strlen(s + 1);
  for (int i = 2; i <= n; i++) {
    int cur = fail[i - 1];
    while (cur && s[cur + 1] != s[i]) cur = fail[cur];
    if (s[cur + 1] == s[i]) cur++;
    fail[i] = cur;
  }
  int x = fail[n];
  while (n % (n - x)) {
    x = fail[x];
  }
  n = n - x;
  s[n + 1] = '\0';
  int i = 0, j = 1, k = 0;
  while (i < n && j < n && k < n) {
    int t = s[(i + k) % n + 1] - s[(j + k) % n + 1];
    if (!t) k++;
    else {
      if (t > 0) i += k + 1;
      else j += k + 1;
      if (i == j) j++;
      k = 0;
    }
  }
  rotate(s + 1, s + min(i, j) + 1, s + n + 1);
  return string(s + 1);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    auto str = prework(s);
    bag[str.length()].push_back(str);
  }
  vector<string> allS;
  for (int i = 1; i < maxn; i++) {
    if (bag[i].empty()) continue;
    sort(begin(bag[i]), end(bag[i]));
    bag[i].resize(unique(begin(bag[i]), end(bag[i])) - begin(bag[i]));
    for (auto& s: bag[i]) {
      allS.push_back(s);
    }
  }
  if (allS.size() == 1) {
    puts("-1");
    return 0;
  }
  sam::clear();
  for (int i = 0; i < 6 * allS[1].size(); i++) {
    sam::insert(allS[1][i % allS[1].size()] - 'a');
  }
  sam::rsort();
  for (int i = 1; i <= sam::sz; i++) {
    ans[i] = sam::len[i];
  }
  auto run = [&](string& s, int mxlen) {
    // ms(dep, 0);
    for (int i = maxn - 1; i >= 0; i--) dep[i] = 0;
    int u = 1, l = 0, n = s.length();
    for (int i = 0; i < mxlen; i++) {
      int c = s[i % n] - 'a';
      if (ch[u][c]) {
        u = ch[u][c], l++;
      } else {
        while (u && !ch[u][c]) u = link[u];
        if (!u) u = 1, l = 0;
        else l = sam::len[u] + 1, u = ch[u][c];
      }
      dep[u] = max(dep[u], l);
    }
    for (int i = sam::sz; i >= 1; i--) {
      int u = sam::a[i];
      dep[link[u]] = max(dep[u], dep[link[u]]);
    }
    for (int i = sam::sz; i >= 1; i--) ans[i] = min(ans[i], dep[i]);
  };
  for (int i = 2; i < allS.size(); i++) {
    run(allS[i], 6 * allS[i].length());
  }
  int mxlen = (int)allS.front().length() * (6 * allS.back().length() / allS.front().length() + 1);
  run(allS.front(), mxlen);
  ll res = 0;
  for (int i = 1; i <= sam::sz; i++) {
    // dbg(sam::len[link[i]], ans[i]);
    res += max(0, ans[i] - sam::len[link[i]]);
  }
  cout << res << endl;
  return 0;
}