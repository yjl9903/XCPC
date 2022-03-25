#pragma GCC optimize(3)
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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

char s[maxn];
vector<string> split(const string& s, char c = ',') {
  int l = s.length();
  vector<string> v;
  int last = 0;
  for (int i = 0; i <= l; i++) {
    if (i == l || s[i] == c) {
      v.push_back(s.substr(last, i - last));
      last = i + 1;
    }
  }
  return v;
}

int n, first, last, fb[20], rks[305];

struct MySolve {
  int t, w, id;
  MySolve() {}
  MySolve(int a, int b, int c): t(a), w(b), id(c) {}
};

struct Node {
  int fs;
  vector<int> sl;

  Node() {}
  Node(int a, vector<int> v): fs(a), sl(v) {}
  Node(const vector<string>& v) {
    fs = 0; sl.clear();
    // assert((int)v.size() == 10);
    for (int i = 0; i < 10; i++) {
      if (v[i] == "-") continue;
      int t, w; sscanf(v[i].c_str(), "%d %d", &t, &w);
      sl.push_back(t);
      first = min(first, t);
      fb[i] = min(fb[i], t);
      last = max(last, t);
      fs += t + w * 20;
    }
    sort(begin(sl), end(sl), greater<int>());
  }
  bool operator<(const Node& b) const {
    if (sl.size() != b.sl.size()) {
      return sl.size() > b.sl.size();
    }
    if (fs != b.fs) {
      return fs < b.fs;
    }
    return sl < b.sl;
  }
} a[305];

vector<MySolve> me;
vector<int> p;
inline int cal() {
  int ans = 0, tot = 0, fs = 0;
  vector<int> sl;
  int mn = 300000, mx = 0;
  for (int i: p) {
    int t = me[i].t, w = me[i].w, id = me[i].id;
    tot += t;
    if (tot > 300) break;
    mn = min(mn, tot); mx = tot;
    if (tot <= fb[id]) ans += 800;
    sl.push_back(tot);
    fs += tot + w * 20;
  }
  reverse(begin(sl), end(sl));
  if (!sl.empty() && mn <= first) ans += 700;
  if (!sl.empty() && mx >= last) ans += 500;
  int rk = lower_bound(a + 1, a + n, Node(fs, sl)) - a;
  return ans + rks[rk];
}

int main() {
  first = 300000;
  for (int i = 0; i < 10; i++) fb[i] = 300000;

  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int ans = 5000 / i;
    if (i <= n / 10) ans += 1200;
    else if (i <= 3 * (n / 10)) ans += 800;
    else if (i <= 6 * (n / 10)) ans += 400;
    rks[i] = ans;
  }
  for (int i = 1; i < n; i++) {
    getchar(); scanf("%[^\n]", s);
    a[i] = Node(split(s));
  }
  sort(a + 1, a + n);

  getchar(); scanf("%[^\n]", s);
  auto v = split(s);
  // assert((int)v.size() == 10);
  
  for (int i = 0; i < 10; i++) {
    if (v[i] == "-") continue;
    int t, w; sscanf(v[i].c_str(), "%d %d", &t, &w);
    me.emplace_back(t, w, i);
    p.push_back(p.size());
  }

  int ans = 0;
  do {
    ans = max(ans, cal());
  } while (next_permutation(begin(p), end(p)));
  if (me.empty()) {
    int rk = n;
    for (int i = 1; i < n; i++) {
      if (a[i].sl.empty()) {
        rk = i; break;
      }
    }
    ans = rks[rk];
  }

  printf("%d\n", ans);
  return 0;
}