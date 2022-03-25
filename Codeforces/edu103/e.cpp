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
const int maxn = 200000 + 5;

int n, m, k, ans[maxn], in[maxn];
char pat[maxn][8], s[8];
map<int,int> rid;
vector<int> edge[maxn];

int cal(const char s[]) {
  int res = 0;
  for (int i = 0; i < k; i++) {
    res *= 27;
    if (s[i] == '_') res += 26;
    else res += s[i] - 'a';
  }
  return res;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%s", pat[i]);
    rid[cal(pat[i])] = i;
  }
  for (int i = 1; i <= m; i++) {
    int x;
    scanf("%s%d", s, &x);
    string ss(s);
    set<string> st;
    dbg(i, ss);
    for (int s = 0; s < (1 << k); s++) {
      auto str = ss;
      for (int j = 0; j < k; j++) {
        if (s >> j & 1) {
          if (str[j] != '_') {
            str[j] = '_';
          }
        }
      }
      st.insert(str);
    }
    bool flag = false, flag2 = false;
    for (auto& str: st) {
      int val = cal(str.c_str());
      int id = rid[val];
      if (id) {
        flag = true;
        dbg(x, str, id);
        if (x != id) {
          edge[x].push_back(id);
          in[id]++;
        } else {
          flag2 = true;
        }
      }
    }
    if (!flag || !flag2) return puts("No"), 0;
  }
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (in[i] == 0) {
      q.push(i);
    }
  }
  vector<int> ans;
  while (!q.empty()) {
    int u = q.front();
    ans.push_back(u);
    q.pop();
    for (int v: edge[u]) {
      in[v]--;
      if (in[v] == 0) {
        q.push(v);
      }
    }
  }
  if (ans.size() == n) {
    puts("Yes");
    for (int x: ans) printf("%d ", x);
  } else {
    puts("No");
  }
  return 0;
}