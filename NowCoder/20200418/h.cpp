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
#include <unordered_map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n;

unordered_map<int,int> pre, siz;
int find(int x) {
  if (pre.count(x)) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
  } else {
    pre[x] = x;
    siz[x] = 1;
    return x;
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    pre.clear(); siz.clear();
    vector<PII> vec;
    for (int i = 1; i <= n; i++) {
      int a, b, c; scanf("%d%d%d", &a, &b, &c);
      if (c == 1) {
        a = find(a); b = find(b);
        if (a != b) {
          if (siz[a] > siz[b]) swap(a, b);
          siz[b] += siz[a]; pre[a] = b;
        }
      } else {
        vec.push_back({ a, b });
      }
    }
    bool flag = true;
    for (auto& x: vec) {
      if (find(x.first) == find(x.second)) {
        flag = false;
        break;
      }
    }
    if (flag) puts("YES");
    else puts("NO");
  }
  return 0;
}