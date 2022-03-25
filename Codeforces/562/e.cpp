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

int n, q, a[maxn], nxt[maxn][21], nx[21];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 0; i < 21; i++) nxt[n + 1][i] = nx[i] = n + 1;
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < 21; j++) nxt[i][j] = n + 1;
        for (int j = 0; j < 21; j++) if (a[i] & (1 << j)) {
            int p = nx[j];
            nx[j] = nxt[i][j] = i;
            for (int k = 0; k < 21; k++) {
                nxt[i][k] = min(nxt[i][k], nxt[p][k]);
            }
        }
    }
    int l, r;
    while (q--) {
        scanf("%d%d", &l, &r);
        int f = 0;
        for (int j = 0; j < 21; j++) if (a[r] & (1 << j)) {
            if (nxt[l][j] <= r) {
                dbg(nxt[l][j]);
                f = 1; break;
            }
        }
        if (f) puts("Shi");
        else puts("Fou");
    }
    return 0;
}