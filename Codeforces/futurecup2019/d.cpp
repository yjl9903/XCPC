#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

void exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1; y = 0; return ;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int m, a, b, dis[maxn], vis[maxn];

int main() {
    cin >> m >> a >> b;
    for (int i = 1; i <= a + b; i++) dis[i] = inf;
    int mx = 0, tot = 0;
    while (true) {
        if (tot >= b) {
            tot -= b;
        } else {
            tot += a;
        }
        if (dis[tot] != inf) break;
        mx = max(mx, tot);
        dis[tot] = mx;
    }
    ll ans = 0;
    for (int i = 0; i < a + b; i++) {
        if (dis[i] == inf) continue;
        ans += max(0, m - dis[i] + 1);
    }
    if (m >= a + b) {
        int g = gcd(a, b);
        int r = m - (a + b) + 1;
        int l = r % g;
        ans += 1ll * (l + r) * ((r - l) / g + 1) / 2;
    }
    cout << ans << endl;
    return 0;
}