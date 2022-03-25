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

int n, k, L[maxn], R[maxn], tL[maxn], tR[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", L + i, R + i);
    }
    int tl = L[1], tr = R[1];
    tL[1] = L[1]; tR[1] = R[1];
    bool flag = true;
    for (int i = 2; i <= n; i++) {
      int nl = tl - k, nr = tr + k;
      tl = max(nl, L[i]);
      tr = min(nr, R[i]);
      tL[i] = tl;
      tR[i] = tr;
      if (tl > tr) {
        flag = false;
        break;
      }
    }
    if (flag) {
      puts("YES");
      vector<int> ans = { tL[n] };
      for (int i = n - 1; i >= 1; i--) {
        int pre = ans.back();
        int l = max(pre - k, tL[i]), r = min(pre + k, tR[i]);
        assert(l <= r);
        if (abs(l - pre) <= k) {
          ans.push_back(l);
        } else if (abs(r - pre) <= k) {
          ans.push_back(r);
        } else {
          assert(false);
        }
      }
      reverse(begin(ans), end(ans));
      for (int i = 0; i < n; i++) {
        printf("%d%c", ans[i], " \n"[i + 1 == n]);
      }
    } else {
      puts("NO");
    }
  }
  return 0;
}