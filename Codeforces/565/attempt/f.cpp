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
const int maxn = 100000 + 5;

int n;
ll f[20][5], g[20][5];

int main() {
    for (int i = 0; i <= 10; i++) for (int j = 0; j <= 3; j++) f[i][j] = g[i][j] = -1;
    f[0][0] = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        // dbg("-----");
        int k, c, d; scanf("%d", &k);
        while (k--) {
            scanf("%d%d", &c, &d);
            for (int i = 0; i <= 9; i++) for (int j = 0; j <= 3; j++) g[i][j] = -1;
            for (int i = 0; i <= 9; i++) {
                for (int j = 0; j + c <= 3; j++) {
                    if (f[i][j] == -1) continue;
                    if (i == 9) g[0][j + c] = max(g[0][j + c], f[i][j] + 2ll * d);
                    else g[i + 1][j + c] = max(g[i + 1][j + c], f[i][j] + d);
                }
            }
            for (int i = 0; i <= 9; i++) {
                // dbg(i);
                for (int j = 0; j <= 3; j++) {
                    g[i][j] = max(f[i][j], g[i][j]);
                    // dbg(g[i][j]);
                }
                // dbg("");
            }
            swap(f, g);
        }
        for (int i = 0; i <= 9; i++) {
            // dbg(i); 
            g[i][0] = f[i][0];
            for (int j = 1; j <= 3; j++) {
                // dbg(f[i][j]);
                g[i][0] = max(g[i][0], f[i][j]);
                g[i][j] = -1;
            }
            // dbg(g[i][0]);
            // puts("");
        }
        swap(f, g);
    }
    ll ans = 0;
    for (int i = 0; i <= 9; i++) for (int j = 0; j <= 3; j++) ans = max(ans, f[i][j]);
    cout << ans;
    return 0;
}