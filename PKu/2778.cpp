#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
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
const int mod = 100000;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int M = 101;

struct Mat {
    ll a[101][101];
    Mat() { ms(a, 0); }
    void clear() { ms(a, 0); }
    void eye() { for (int i = 0; i < M; i++) a[i][i] = 1; }
    ll* operator [] (ll x) { return a[x]; }
    const ll* operator [] (ll x) const { return a[x]; }
    Mat operator * (const Mat& b) {
        const Mat& a = *this; Mat r;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < M; k++)
                    r[i][j] = (r[i][j] + a[i][k] * b[k][j]);
                r[i][j] %= mod;
            }
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
} f, g;

namespace ACAM {
    static const int maxp = 100000 + 5;
    int sz, ch[maxp][4], fail[maxp];
    int danger[maxp];
    int node() {
        ms(ch[++sz], 0); fail[sz] = danger[sz] = 0;
        return sz;
    }
    void clear() {
        sz = 0; node();
        for (int i = 0; i < 4; i++) ch[0][i] = 1;
    }
    int get(char s) {
        if (s == 'A') return 0;
        if (s == 'T') return 1;
        if (s == 'G') return 2;
        if (s == 'C') return 3;
        return -1;
    }
    void insert(char* s, int i) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            int v = get(s[i]);
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        danger[u] = 1;
    }
    void build() {
        queue<int> q; q.push(1);
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 0; i < 4; i++) {
                if (ch[t][i]) {
                    fail[ch[t][i]] = ch[fail[t]][i];
                    danger[ch[t][i]] |= danger[fail[ch[t][i]]];
                    q.push(ch[t][i]);
                } else {
                    ch[t][i] = ch[fail[t]][i];
                }
            }
        }
    }
} using namespace ACAM;

int m; ll n;
char s[maxn];

int main() {
    while (scanf("%d%lld", &m, &n) == 2) {
        clear();
        for (int i = 1; i <= m; i++) {
            scanf("%s", s); insert(s, i);
        }
        ACAM::build();
        f.clear(); g.clear(); g[0][0] = 1;
        for (int i = 1; i <= sz; i++) {
            for (int j = 0; j < 4; j++) {
                if (danger[ch[i][j]]) continue;
                f[ch[i][j] - 1][i - 1]++;
            }
        }
        M = sz;
        Mat res = f.pow(n) * g;
        // res.print();
        ll ans = 0;
        for (int i = 0; i < sz; i++) ans = (ans + res[i][0]);
        printf("%lld\n", ans % mod);
    }
    return 0;
}