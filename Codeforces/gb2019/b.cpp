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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    int ansl = -1, ansr = -1;
    map<int,int> mp;
    for (int i = 1; i <= n; i++) {
      auto it = mp.upper_bound(a[i] - i);
      if (it != mp.begin()) {
        it--;
        ansl = it->second; ansr = i;
      }
      mp[a[i] - i + 1] = i;
    }

    mp.clear(); reverse(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++) {
      auto it = mp.upper_bound(a[i] - i);
      if (it != mp.begin()) {
        it--;
        ansr = n - it->second + 1; ansl = n - i + 1;
      }
      mp[a[i] - i + 1] = i;
    }
    
    if (ansl == -1) {
      puts("NO");
    } else {
      puts("YES");
      printf("%d %d\n", ansl, ansr);
    }
  }
  return 0;
}