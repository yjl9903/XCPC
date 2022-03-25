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

int n, a[maxn], b[maxn], cnt[maxn];

int cal() {
  for (int i = 1; i <= n; i++) {
    cnt[a[i]]++;
  }
  int r = 0;
  while (cnt[r] > 0) r++;
  for (int i = 1; i <= n; i++) {
    cnt[a[i]]--;
  }
  return r;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      b[i] = a[i];
    }
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
      if (b[i] == 0) {
        ans.push_back(i);
        a[i] = cal();
      }
    }
    #ifdef XLor
    cout << "a: ";
    for (int i = 1; i <= n; i++) {
      cout << a[i] << ' ';
    }
    cout << endl;
    #endif
    for (int i = 1; i <= n; i++) {
      if (b[i] > 0) {
        ans.push_back(i);
        a[i] = cal();
      }
    }
    
    for (int i = 1; i <= n; i++) {
      ans.push_back(i);
      a[i] = cal();
    }
    #ifdef XLor
    cout << "a: ";
    for (int i = 1; i <= n; i++) {
      cout << a[i] << ' ';
    }
    cout << endl;
    #endif
    printf("%d\n", ans.size());
    for (int x: ans) {
      printf("%d ", x);
    }
    puts("");
  }
  return 0;
}