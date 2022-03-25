#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const int maxn = 200000 + 5;

int n;
vector<int> bag[maxn];

ll get(int x) {
    return 1ll * x * (x - 1) / 2ll;
}

int main() {
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        bag[u].push_back(i);
        bag[v].push_back(i);
    }
    ll ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans += 1ll * (n + i) * (n - 1 - i) / 2;
    }
    for (int i = 1; i <= n; i++) {
        sort(bag[i].begin(), bag[i].end());
        int last = 0;
        for (int& x: bag[i]) {
            ans -= get(x - last);
            last = x;
        }
        ans -= get(n - last);
    }
    cout << ans << endl;
    return 0;
}