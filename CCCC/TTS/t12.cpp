#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int maxn = 100000 + 5;

int n, m;
vector<int> nxt[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    int k;
    scanf("%d", &k);
    while (k--) {
      int x;
      scanf("%d", &x);
      nxt[i].push_back(x);
    }
  }
  int cur = 1;
  vector<int> save(128, -1);
  for (int i = 1; i <= m; i++) {
    int op;
    scanf("%d", &op);
    if (op == 0) {
      int x;
      scanf("%d", &x);
      cur = nxt[cur][x - 1];
    } else if (op == 1) {
      int x;
      scanf("%d", &x);
      save[x] = cur;
      printf("%d\n", cur);
    } else if (op == 2) {
      int x;
      scanf("%d", &x);
      cur = save[x];
      assert(cur != -1);
    }
  }
  printf("%d\n", cur);
  return 0;
}