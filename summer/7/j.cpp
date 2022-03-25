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
const int maxn = 1000 + 5;

struct Trie {
    int sz, ch[maxn * 40][2], val[maxn * 40];
    void clear() {
        sz = 1; val[1] = 0;
        ch[1][0] = ch[1][1] = 0;
    }
    void insert(ll x, int v) {
        int u = 1;
        for (int i = 32; i >= 0; i--) {
            int b = x >> i & 1;
            if (!ch[u][b]) {
                ch[u][b] = ++sz; 
                ch[sz][0] = ch[sz][1] = 0;
                val[sz] = 0;
            }
            val[u] += v;
            u = ch[u][b];
        }
        val[u] += v;
    }
    ll query(ll x) {
        int u = 1;
        ll ans = x;
        for (int i = 32; i >= 0; i--) {
            // dbg(u, i, ch[u][0], ch[u][1], val[ch[u][0]], val[ch[u][1]]);
            int b = x >> i & 1;
            // dbg(b, u, ch[u][0], ch[u][1]);
            // dbg(val[ch[u][0]], val[ch[u][1]]);
            if (ch[u][b ^ 1] && val[ch[u][b ^ 1]]) {
                ans |= 1 << i; u = ch[u][b ^ 1];
            } else {
                // dbg(ch[u][b]);
                // assert(ch[u][b] && val[ch[u][b]]);
                ans ^= b << i; u = ch[u][b];
            }
        }
        return ans;
    }
} f;

int n, a[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        f.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i); f.insert(a[i], 1);
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            f.insert(a[i], -1);
            for (int j = i + 1; j <= n; j++) {
                f.insert(a[j], -1);
                ans = max(ans, f.query(a[i] + a[j]));
                f.insert(a[j], 1);   
            }
            f.insert(a[i], 1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}