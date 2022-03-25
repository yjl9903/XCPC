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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 5 + 5;

int n, m, k;
PII c[maxn * maxn];

int mp[maxn][maxn];
// void show() {
//     for (int i = 1; i <= n; i++) {
//         for (int j = 1; j <= m; j++) {
//             printf("%d%c", mp[i][j], " \n"[j == m]);
//         }
//     }
//     puts("");
// }
int dfs(int x, int y) {
    // dbg(x, y);
    // show(); mp[x][y] = i;
    if (x > n) return 1;
    int nx = x, ny = y + 1;
    if (ny > m) nx++, ny = 1;
    for (int i = 1; i <= k; i++) {
        if (c[i].first == 0) continue;
        if (x > 1 && mp[x - 1][y] == c[i].second) continue; 
        if (y > 1 && mp[x][y - 1] == c[i].second) continue;
        c[i].first--; mp[x][y] = c[i].second;
        if (dfs(nx, ny)) return 1;
        c[i].first++; mp[x][y] = 0;
    }
    return 0;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        int flag = 1; int sum = n * m / 2 + n * m % 2;
        // dbg(sum);
        for (int i = 1; i <= k; i++) {
            scanf("%d", &c[i].first), c[i].second = i;
            // dbg(c[i].first, c[i].second);
            if (c[i].first > sum) flag = 0;
        }
        printf("Case #%d:\n", ++kase);
        if (flag == 0) {
            puts("NO"); continue;
        }
        sort(c + 1, c + 1 + k); reverse(c + 1, c + 1 + k);
        flag = dfs(1, 1);
        if (flag) {
            puts("YES");
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    printf("%d%c", mp[i][j], " \n"[j == m]);
                }
            }
        } else puts("NO");
    }
    return 0;
}