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
const int maxn = 100000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}

struct Mat {
    static const int M = 3;
    ll a[M][M];
    Mat() { ms(a, 0); }
    void clear() { ms(a, 0); }
    void eye() { for (int i = 0; i < M; i++) a[i][i] = 1; }
    ll* operator [] (ll x) { return a[x]; }
    const ll* operator [] (ll x) const { return a[x]; }
    Mat operator * (const Mat& b) {
        int mod = 1e9 + 6;
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
} h, h2, g1, g2, g3, gc;

ll n, f1, f2, f3, c;

int main() {
    cin >> n >> f1 >> f2 >> f3 >> c;
    g1[0][0] = 0; g1[1][0] = 0; g1[2][0] = 1;
    g2[0][0] = 0; g2[1][0] = 1; g2[2][0] = 0;
    g3[0][0] = 1; g3[1][0] = 0; g3[2][0] = 0;
    gc[0][0] = 3; gc[1][0] = 2; gc[2][0] = 1;

    h[0][0] = h[0][1] = h[0][2] = 1;
    h[1][0] = 1;
    h[2][1] = 1;
    h2 = h.pow(n - 3);

    ll x1 = (h2 * g1)[0][0];
    ll x2 = (h2 * g2)[0][0];
    ll x3 = (h2 * g3)[0][0];
    ll x4 = ((h2 * gc)[0][0] - n % (mod - 1) + mod - 1) % (mod - 1);

    dbg(x1, x2, x3, x4);

    ll ans = qpow(f1, x1) * qpow(f2, x2) % mod * qpow(f3, x3) % mod * qpow(c, x4) % mod;

    cout << ans << '\n';
    return 0;
}