#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
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
const int maxn = 300000 + 5;

int n, m, a[maxn], b[maxn];

int cal(int a, int x) {
    if (a < x) return a + m - x;
    return a - x;
}

int check(int x) {
    for (int i = 1; i <= n; i++) b[i] = a[i];
    for (int i = 1; i <= n; i++) {
        if (b[i] + x >= m && (b[i] + x) % m >= b[i - 1]) b[i] = b[i - 1];
        else if (b[i] >= b[i - 1]) ;
        else if (b[i] + x < m && b[i] + x >= b[i - 1]) b[i] = b[i - 1];
        else if (b[i] + x >= m) b[i] = b[i - 1];
        else return 0;
        // dbg(i, b[i], b[i - 1]);
    }
    return 1;
}

int dp[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    // check(0);
    // check(1);
    int l = 0, r = m - 1, ans = 0;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) ans = m, r = m - 1;
        else l = m + 1;
    }
    cout << ans;
    return 0;
}