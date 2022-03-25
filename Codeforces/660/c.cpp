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

// kirakira, dokidoki!!!
int n, m, kirakira[maxn], dokidoki[maxn];
vector<int> HelloHappyWorld[maxn];

// Happy, lucky, smile, yeah!!!
ll happy[maxn], lucky[maxn], smile[maxn], yeah;
void houkongfan(int u, int f) {
  smile[u] = kirakira[u];
  happy[u] = 0;
  lucky[u] = 0;
  int c = 0;
  for (int v: HelloHappyWorld[u]) {
    if (v == f) continue;
    c++;
    houkongfan(v, u);
    if (!yeah) return ;
    smile[u] += smile[v];
    happy[u] += happy[v];
    lucky[u] += lucky[v];
  }
  if (c == 0) {
    if (kirakira[u] >= dokidoki[u] && (kirakira[u] - dokidoki[u]) % 2 == 0) {
      lucky[u] = (kirakira[u] - dokidoki[u]) / 2;
      happy[u] = kirakira[u] - lucky[u];
      if (happy[u] < 0 || lucky[u] < 0) {
        yeah = false;
      }
    } else {
      yeah = false;
    }
  } else {
    if (smile[u] >= dokidoki[u] && (smile[u] - dokidoki[u]) % 2 == 0) {
      ll luc = (smile[u] - dokidoki[u]) / 2;
      ll hap = smile[u] - luc;
      if (luc < 0 || hap < 0) {
        yeah = false;
      }
      if (hap < happy[u]) {
        yeah = false;
      }
      happy[u] = hap;
      lucky[u] = luc;
    } else {
      yeah = false;
    }
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      HelloHappyWorld[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", kirakira + i);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", dokidoki + i);
    }
    for (int i = 2, u, v; i <= n; i++) {
      scanf("%d%d", &u, &v);
      HelloHappyWorld[u].push_back(v);
      HelloHappyWorld[v].push_back(u);
    }
    yeah = true;
    houkongfan(1, 0);
    puts(yeah ? "YES" : "NO");
  }
  return 0;
}