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
const int maxn = 10 + 5;

int dir[4][2] = { 1, 0, 0, 1, -1, 0, 0, -1 };

int n, m, nn;
char s[maxn][maxn];
vector<PII> bag[20];
int col[20][20], ok[20][20];

int vis[20][20];
PII nxt[20][20];
int find(int x, int y) {
    // dbg(x, y);
    for (int k = 0; k < 4; k++) {
        int tx = x + dir[k][0], ty = y + dir[k][1];
        if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
        if (!ok[tx][ty]) continue;
        if (vis[tx][ty]) continue;
        vis[tx][ty] = 1;
        if (nxt[tx][ty].first == -1 || find(nxt[tx][ty].first, nxt[tx][ty].second)) {
            nxt[tx][ty] = { x, y }; return true;
        }
    }
    return false;
}
int match() {
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) nxt[i][j] = {-1,-1};
    int sum = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) 
        if ((i + j) % 2 == 0 && ok[i][j]) {
            // dbg(i, j);
            ms(vis, 0); 
            if (find(i, j)) sum++;
        }
    return sum;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i][j] == '.') continue;
                bag[s[i][j] - '0'].push_back({i, j});
            }
        }
        int ans = 0;
        for (int s = 0; s < 1024; s++) {
            ms(col, 0); ms(ok, 0); int f = 0, tot = 0;
            for (int i = 0; i < 10; i++) if (s & (1 << i)) {
                tot++;
                if (bag[i].empty()) {
                    f = 1; break;
                }
                for (auto& x: bag[i]) {
                    int ccc = i + 1;
                    col[x.first][x.second] = i + 1;
                    for (int i = 0; i < 4; i++) {
                        int tx = x.first + dir[i][0], ty = x.second + dir[i][1];
                        if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
                        if (col[tx][ty] && col[tx][ty] != ccc) {
                            f = 1; break;
                        }
                    }
                    if (f) break;
                }
            }
            if (f) continue;
            // dbg(s);
            nn = 0;
            for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
                if (col[i][j]) continue;
                if (::s[i][j] != '.') continue;
                // dbg(i, j);
                int flag = 0;
                for (int k = 0; k < 4; k++) {
                    int tx = i + dir[k][0], ty = j + dir[k][1];
                    if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
                    if (col[tx][ty]) flag = 1;
                    // dbg(tx, ty, col[tx][ty]);
                }
                if (flag) continue;
                nn++; ok[i][j] = 1;
            }
            // for (int i = 1; i <= n; i++) {
            //     for (int j = 1; j <= m; j++) putchar(ok[i][j] + '0');
            //     puts("");
            // }
            // dbg(nn, match());
            ans = max(ans, tot + nn - match());
        }
        printf("Case #%d: %d\n", ++kase, ans);
        for (int i = 0; i <= 9; i++) bag[i].clear();
    }
    return 0;
} 