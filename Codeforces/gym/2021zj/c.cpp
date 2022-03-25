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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int sqr(int x) {
  return x * x;
}

int x[maxn], y[maxn], z[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    set<tuple<int,int, int> > st;
    for (int i = 0; i < 8; i++) {
      scanf("%d%d%d", x + i, y + i, z + i);
      st.emplace(x[i], y[i], z[i]);
    }
    if (st.size() != 8) {
      puts("NO");
      continue;
    }
    vector<int> len;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < i; j++) {
        int dx = x[i] - x[j];
        int dy = y[i] - y[j];
        int dz = z[i] - z[j];
        len.push_back(sqr(dx) + sqr(dy) + sqr(dz));
      }
    }
    assert(len.size() == 28);
    sort(len.begin(), len.end());
    bool flag = true;
    for (int i = 1; i < 12; i++) {
      if (len[i] != len[0]) {
        flag = false;
      }
    }
    for (int j = 12; j < 24; j++) {
      if (len[j] != 2 * len[0]) {
        flag = false;
      }
    }
    for (int j = 24; j < 28; j++) {
      if (len[j] != 3 * len[0]) {
        flag = false;
      }
    }
    puts(flag ? "YES" : "NO");
  }
  return 0;
}