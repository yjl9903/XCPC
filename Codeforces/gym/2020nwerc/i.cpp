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

int n, d[maxn], t[3][maxn];
int pred[maxn], pret[3][maxn];

int len(int x, int from, int to) {
  if (from == to) {
    return 0;
  } else if (from < to) {
    int ans = pred[to - 1] - (from == 0 ? 0 : pred[from - 1]);
    ans += pret[x][to - 1] - (from == 0 ? 0 : pret[x][from - 1]);
    return ans;
  } else {
    return len(x, from, to + n);
  }
}

set<PII> edge[4];

void prework(int T, int x, int y) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      bool flag = true;
      for (int k = 0; k < n; k++) {
        int l1 = len(x, i, k);
        int r1 = l1 + t[x][k];
        int l2 = len(y, j, k);
        int r2 = l2 + t[y][k];
        if (min(r1, r2) > max(l1, l2)) {
          flag = false;
          break;
        }
      }
      if (flag) {
        edge[T].insert({ i, j });
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", d + i);
    pred[i] = d[i];
    if (i > 0) pred[i] += pred[i - 1];
  }
  for (int i = n; i < n + n; i++) {
    d[i] = d[i - n];
    pred[i] = d[i] + pred[i - 1];
  }
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < n; i++) {
      scanf("%d", &t[j][i]);
      pret[j][i] = t[j][i];
      if (i > 0) pret[j][i] += pret[j][i - 1];
    }
    for (int i = n; i < n + n; i++) {
      t[j][i] = t[j][i - n];
      pret[j][i] = t[j][i];
      pret[j][i] += pret[j][i - 1];
    }
  }
  prework(0, 0, 1);
  prework(1, 1, 2);
  prework(2, 0, 2);
  int ansx = -1, ansy = -1, ansz = -1;
  for (int i = 0; i < n && ansx == -1; i++) {
    for (int j = 0; j < n && ansx == -1; j++) {
      if (!edge[0].count({ i, j })) continue;
      for (int k = 0; k < n && ansx == -1; k++) {
        if (edge[1].count({ j, k })) {
          if (edge[2].count({ i, k })) {
            ansx = i + 1;
            ansy = j + 1;
            ansz = k + 1;
          }
        }
      }
    }
  }
  if (ansx != -1) {
    printf("%d %d %d\n", ansx, ansy, ansz);
  } else {
    puts("impossible");
  }
  return 0;
}