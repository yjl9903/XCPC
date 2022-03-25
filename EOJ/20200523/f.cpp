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

int n, k;
char s[maxn];

vector<string> split(const string& s) {
  vector<string> v;
  int last = 1;
  for (int i = 1; i < (int)s.length(); i++) {
    if (s[i] == '/') {
      v.push_back(s.substr(last, i - last));
      last = i + 1;
    }
  }
  v.push_back(s.substr(last));
  return v;
}

int tot = 1;
map<string,int> ch[maxn];

void insert(const vector<string>& v) {
  int u = 1;
  for (int i = 0; i < (int)v.size(); i++) {
    if (!ch[u].count(v[i])) {
      ch[u][v[i]] = ++tot;
    }
    u = ch[u][v[i]];
  }
}

bool check(const string& s) {
  if (s.length() >= 4) {
    return s.substr(s.length() - 4) == ".eoj";
  } else {
    return false;
  }
}

int ans = 0;
void dfs(int u) {
  for (auto& x: ch[u]) {
    int v = x.second;
    if (ch[v].empty()) {
      if (check(x.first)) {
        ans++;
      }
    } else {
      dfs(v);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    auto v = split(s + 1);
    // for (auto& x: v) {
    //   dbg(x);
    // }
    insert(v);
  }
  dfs(1);
  printf("%d\n", ans);
  return 0;
}