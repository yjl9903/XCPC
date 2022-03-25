#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
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
const int maxn = 1000000 + 5;

int n, a[maxn];

int b[maxn];
inline int lowbit(int x) {
    return x & -x;
}
inline void update(int i, int x) {
    for (; i <= n; i += lowbit(i)) b[i] += x;
}
inline int query(int i) {
    int ans = 0;
    for (; i; i -= lowbit(i)) ans += b[i];
    return ans;
} 

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        ms(b, 0);
        int ans = 0;
        scanf("%d", &n);
        vector<PII> v;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            v.push_back({a[i], i});
        }
        sort(v.begin(), v.end(), greater<PII>());
        for (int i = 0; i < n; i++) {
            int x = v[i].second;
            x -= query(x);
            // dbg(i, x);
            if (x != n - i) ans++;
            update(v[i].second, 1);
        }
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}