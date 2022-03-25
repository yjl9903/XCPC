#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int f[maxn], inv[maxn], finv[maxn];
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1; 
    for (int i = 1; i < maxn; i++) {
        f[i] = f[i - 1] * 1ll * i % mod;
        finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
}
int C(int n, int m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}
int H(int n) {
    return (C(2 * n, n) - C(2 * n, n - 1) + mod) % mod;
}

int n, m;
ll dp[2000][2000];

int main() {
    // init();
    // int n, m; cin >> n >> m; n += m;
    // cout << (C(2 * n, n) - C(2 * n, n - 1) + mod) % mod * C(n, m) % mod << endl;
    // int n; cin >> n; cout << H(n) << endl;
    // while (scanf("%d%d", &n, &m) == 2) {
    //     dp[0][0] = 1;
    //     for (int i = 1; i <= n + m; i++) {
    //         dp[i][0] = 1;
    //         for (int j = 1; j <= m; j++) {

    //         }
    //     }
    // }
    init();
    int n, m; cin >> n >> m;
    int ans = C(2 * (n + m), n + m) - C(n + m, m);
    cout << (ans + mod) % mod;
    return 0;
}