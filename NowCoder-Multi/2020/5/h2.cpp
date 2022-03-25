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

int n, q, a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  scanf("%d", &q);
  int ans = 0;
  while (q--) {
    int ql, qr;
    scanf("%d%d", &ql, &qr);
    ql = (ql ^ ans) % n + 1;
    qr = (qr ^ ans) % n + 1;
    if (ql > qr) swap(ql, qr);
    set<int> st;
    for (int l = ql; l <= qr; l++) {
      for (int r = l; r <= qr; r++) {
        int tot = a[l];
        for (int i = l; i <= r; i++) {
          tot &= a[i];
        }
        st.insert(tot);
      }
    }
    printf("%d %d %d\n", ql, qr, ans = st.size());
  }
  return 0;
}