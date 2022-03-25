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
const int maxn = 500 + 5;

int n, m, a[maxn][maxn], c[maxn][2], p[maxn][2];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int t = 0; t <= 10; t++) {
        int x = 0, y = 0, z = 0;
        vector<int> ans(n + 1, 0);
        ms(c, 0); ms(p, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // dbg(t, a[i][j] >> t & 1);
                c[i][a[i][j] >> t & 1]++;
                p[i][a[i][j] >> t & 1] = j;
            }
            if (c[i][1] && !c[i][0]) x++, ans[i] = p[i][1];
        }
        for (int i = 1; i <= n; i++) {
            if (ans[i]) continue;
            if (c[i][1] && (x % 2 == 0)) {
                ans[i] = p[i][1]; x++;
            } else ans[i] = p[i][0];
            dbg(c[i][1]);
        }
        if (x % 2 == 1) {
            dbg(t, x);
            puts("TAK");
            for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
            return 0;
        }
    }
    puts("NIE");
    return 0;
}