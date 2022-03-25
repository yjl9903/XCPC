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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 5000 + 5;

map<char, vector<int> > ch;

int n, m, a[maxn], f[maxn];
int len[maxn], diff[maxn][maxn];
string str[maxn];
char buf[maxn];

void init() {
  ch['A'] = { 1, 1, 3 };
  ch['B'] = { 3, 1, 1, 1, 1, 1, 1 };
  ch['C'] = { 3, 1, 1, 1, 3, 1, 1 };
  ch['D'] = { 3, 1, 1, 1, 1 };
  ch['E'] = { 1 };
  ch['F'] = { 1, 1, 1, 1, 3, 1, 1 };
  ch['G'] = { 3, 1, 3, 1, 1 };
  ch['H'] = { 1, 1, 1, 1, 1, 1, 1 };
  ch['I'] = { 1, 1, 1 };
  ch['J'] = { 1, 1, 3, 1, 3, 1, 3 };
  ch['K'] = { 3, 1, 1, 1, 3 };
  ch['L'] = { 1, 1, 3, 1, 1, 1, 1 };
  ch['M'] = { 3, 1, 3 };
  ch['N'] = { 3, 1, 1 };
  ch['O'] = { 3, 1, 3, 1, 3 };
  ch['P'] = { 1, 1, 3, 1, 3, 1, 1 };
  ch['Q'] = { 3, 1, 3, 1, 1, 1, 3 };
  ch['R'] = { 1, 1, 3, 1, 1 };
  ch['S'] = { 1, 1, 1, 1, 1 };
  ch['T'] = { 3 };
  ch['U'] = { 1, 1, 1, 1, 3 };
  ch['V'] = { 1, 1, 1, 1, 1, 1, 3};
  ch['W'] = { 1, 1, 3, 1, 3 };
  ch['X'] = { 3, 1, 1, 1, 1, 1, 3 };
  ch['Y'] = { 3, 1, 1, 1, 3, 1, 3 };
  ch['Z'] = { 3, 1, 3, 1, 1, 1, 1 };
}

int main() {
  init();
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", buf);
    str[i] = buf;
  }
  sort(str + 1, str + 1 + n);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < str[i].size(); j++) {
      len[i] += ch[str[i][j]].size();
      if (j > 0) len[i]++;
    }
    assert(len[i] % 2 == 1);
    dbg(i, len[i]);
  }
  {
    int l = 0;
    while (scanf("%s", buf + l + 1) == 1) {
      l += strlen(buf + l + 1);
    }
    dbg(buf + 1);
    assert(l == m);
  }
  if (buf[1] != '+' || buf[m] != '+') {
    puts("-1");
    return 0;
  }
  int tot = 0;
  for (int i = 1, j = 1; i <= m; i = j) {
    while (j <= m && buf[i] == buf[j]) j++;
    a[++tot] = j - i;
    // dbg(tot, a[tot]);
  }
  assert(tot % 2 == 1);
  for (int i = 1; i <= tot; i += 2) {
    for (int j = 1; j <= n; j++) {
      int cnt = 0, p = i;
      for (int k = 0; k < str[j].length(); k++) {
        if (k > 0) {
          if (p == tot + 1) {
            cnt = -1;
            break;
          }
          if (abs(a[p] - 3) <= 1) {
            cnt += abs(a[p] - 3);
          } else {
            cnt = -1;
            break;
          }
          p++;
        }
        auto& vec = ch[str[j][k]];
        for (int q = 0; q < vec.size(); q++, p++) {
          if (p == tot + 1) {
            cnt = -1;
            break;
          }
          if (abs(vec[q] - a[p]) <= 1) {
            cnt += abs(vec[q] - a[p]);
            // dbg(p, vec[q], a[p]);
          } else {
            cnt = -1;
            break;
          }
        }
        if (cnt == -1) break;
      }
      diff[i][j] = cnt;
      if (diff[i][j] != -1) {
        dbg(i, j, cnt);
      }
    }
  }

  for (int i = 0; i <= tot; i++) f[i] = -1;
  f[tot + 1] = 0;
  for (int i = tot + 1; i >= 1; i -= 2) {
    if (f[i] == -1) continue;
    for (int j = 1; j <= m; j++) {
      if (i - len[j] < 1) continue;
      int cur = diff[i - len[j]][j];
      if (cur == -1) continue;
      cur += f[i];
      if (i - len[j] > 1) {
        if (abs(a[i - len[j] - 1] - 5) <= 1) {
          cur += abs(a[i - len[j] - 1] - 5);
        } else {
          continue;
        }
      }
      if (f[i - len[j] - 1] == -1 || f[i - len[j] - 1] > cur) {
        f[i - len[j] - 1] = cur;
        // dbg(i, j, i - len[j] - 1, cur);
      }
    }
    // dbg(i, f[i]);
  }

  if (f[0] == -1) {
    puts("-1");
    return 0;
  }
  printf("%d\n", f[0]);
  int cur = 0;
  while (cur <= tot) {
    for (int j = 1; j <= n; j++) {
      if (diff[cur + 1][j] == -1) continue;
      int d = diff[cur + 1][j];
      if (cur > 0) {
        if (abs(a[cur] - 5) <= 1) {
          d += abs(a[cur] - 5);
        } else {
          continue;
        }
      }
      if (cur + len[j] + 1 <= tot + 1 && f[cur + len[j] + 1] != -1 && f[cur] == f[cur + len[j] + 1] + d) {
        // dbg(cur, len[j]);
        cur += len[j] + 1;
        printf("%s ", str[j].c_str());
        break;
      }
    }
  }
  return 0;
}