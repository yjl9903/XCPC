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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 50000 + 5;

struct Mat {
    static const int M = 10;
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
} a[maxn << 2], tmp;

void pushup(int rt) {
    a[rt] = a[rt << 1] * a[rt << 1 | 1];
}
void update(int i, int l, int r, int rt) {
    if (l == r) {
        a[rt] = tmp;
        return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, lson);
    else update(i, rson);
    pushup(rt);
}

int n, m, q;
char mp[maxn][20];

void get(char* mp) {
    tmp.clear();
    int last = 0;
    for (int i = 0; i <= m; i++) {
        if (mp[i] == '1' || i == m) {
            for (int p = last; p < i; p++) {
                for (int q = last; q < i; q++) {
                    tmp[p][q] = 1;
                }
            }
            last = i + 1;
        }
    }
    // for (int i = 0; i < m; i++) {
    //     for (int j = i; j >= 0 && mp[j] == '0'; j--) tmp[i][j] = 1;
    //     for (int j = i; j < m && mp[j] == '0'; j++) tmp[i][j] = 1;
    // }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; i++) {
        scanf("%s", mp[i]);
        get(mp[i]);
        update(i, 0, n - 1, 1);
    }
    int op, x, y;
    while (q--) {
        scanf("%d%d%d", &op, &x, &y); 
        x--; y--;
        if (op == 1) {
            tmp.clear();
            if (mp[x][y] == '1') {
                mp[x][y] = '0';
            } else {
                mp[x][y] = '1';
            }
            get(mp[x]);
            update(x, 0, n - 1, 1);
        } else {
            printf("%lld\n", a[1][x][y]);
        }
    }
    return 0;
}