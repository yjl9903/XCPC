#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, a[maxn];
vector<int> b;

int main() {
    scanf("%d", &n);
    int zeros = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    sort(a + 1, a + 1 + n);
    int same = 0, pos = 0;
    for (int i = 1; i < n; i++) if (a[i] == a[i + 1]) same++, pos = i;
    if (same >= 2) return puts("cslnb"), 0;
    if (same == 1) {
        ll sum = 0;
        if (a[pos] == 0) return puts("cslnb"), 0;
        a[pos]--; sum++;
        if (pos > 1 && a[pos - 1] == a[pos]) return puts("cslnb"), 0;
        for (int i = 1; i <= n; i++) sum += a[i] - (i - 1);
        if (sum % 2) puts("sjfnb");
        else puts("cslnb");
        return 0;
    }
    ll sum = 0;
    for (int i = 1; i <= n; i++) sum += a[i] - (i - 1);
    if (sum % 2) puts("sjfnb");
    else puts("cslnb");
    return 0;
}