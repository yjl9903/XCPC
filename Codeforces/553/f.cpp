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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
ll inv(ll x) {
    return qpow(x, mod - 2);
}
void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}

struct Mat {
    static const int M = 100 + 5;
    ll a[M][M];
    Mat() { ms(a, 0); }
    void clear() { ms(a, 0); }
    void eye() { for (int i = 0; i < M; i++) a[i][i] = 1; }
    ll* operator [] (ll x) { return a[x]; }
    const ll* operator [] (ll x) const { return a[x]; }
    Mat operator * (const Mat& b) {
        const Mat& a = *this; Mat r;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                for (int k = 0; k < M; k++)
                    r[i][j] = (r[i][j] + a[i][k] * b[k][j]) % mod;
        return r;
    }
    Mat pow(ll n) const {
        Mat a = *this, r; r.eye();
        while (n > 0) {
            if (n & 1)  r = r * a;
            n >>= 1; a = a * a;
        }
        return r;
    }
    Mat operator + (const Mat& b) {
        const Mat& a = *this; Mat r;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                r[i][j] = (a[i][j] + b[i][j]) % mod;
        return r;
    }
    void print() const {
        for (int i = 0; i < M; i++) for (int j = 0; j < M; j++)
            printf("%lld%c", (*this)[i][j], j == M - 1 ? '\n' : ' ');
    }
} F, T;

int n, k, m, a[maxn];
ll dp[2][maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (a[i] == 0) m++;
    }
    int c = 0; for (int i = 1; i <= m; i++) if (a[i] == 0) c++;
    F[c][0] = 1;
    ll iv = inv(n * (n - 1) / 2), c1 = m * (m - 1) / 2, c2 = (n - m) * (n - m - 1) / 2;
    for (int i = 0; i <= m; i++) {
        T[i][i] = 1ll * (c1 + c2 + i * (m - i) + (m - i) * (n - 2 * m + i)) * iv % mod;
        if (i > 0) {
            T[i][i - 1] = 1ll * (m - i + 1) * (m - i + 1) * iv % mod;
        }
        if (i < m) {
            T[i][i + 1] = 1ll * (i + 1) * (n - 2 * m + i + 1) * iv % mod;
        }
    }
    cout << (T.pow(k) * F)[m][0] << endl;
    // dp[0][c] = 1; int f = 0;
    
    // for (int t = 1; t <= k; t++, f ^= 1) {
    //     // ms(dp[f ^ 1], 0);
    //     dbg(t);
    //     for (int i = 0; i <= m; i++) {
    //         dp[f ^ 1][i] = dp[f][i] * (c1 + c2 + i * (m - i) + (m - i) * (n - 2 * m + i)) % mod * iv % mod;
    //         if (i > 0) {
    //             add(dp[f ^ 1][i], dp[f][i - 1] * (m - i + 1) * (m - i + 1) % mod * iv % mod);
    //         }
    //         if (i < m) {
    //             add(dp[f ^ 1][i], dp[f][i + 1] * (i + 1) * (n - 2 * m + i + 1) % mod * iv % mod);
    //         }
    //     }
    // }
    // cout << dp[f][m] << endl;
    return 0;
}