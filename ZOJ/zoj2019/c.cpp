#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
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
const int maxn = 2000 + 5;

int n, m, a, b, mp[maxn][maxn]; ll k;
char s[maxn], cmd[300];
bool vis[maxn][maxn][3];

int f(char c) { return c - '0'; }
char cal(int i, int j) {
    int x = 81 * mp[i][j] + 27 * mp[i - 1][j] + 9 * mp[i + 1][j] + 3 * mp[i][j - 1] + mp[i][j + 1];
    return cmd[x + 1];
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int ans = 0;
        scanf("%d%d%d%d%lld%s", &n, &m, &a, &b, &k, cmd + 1);
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%s", s);
            for (int j = 1; j <= m; j++) {
                mp[i][j] = s[j] - '0';
                if (mp[i][j] == 2) sum++;
                vis[i][j][0] = vis[i][j][1] = vis[i][j][2] = 0;
            }
        }
        int tx = a, ty = b;
        for (int i = 1; i <= k; i++) {
            if (ans == sum) break;
            char op = cal(tx, ty);
            if (op == 'U') {
                int x = tx - 1, y = ty;
                if (vis[x][y][mp[x][y]] == 1) {
                    break;
                } else {
                    if (mp[x][y] == 0) {
                        tx = x; ty = y;
                        vis[x][y][0] = 1;
                    } else if (mp[x][y] == 2) {
                        tx = x; ty = y;
                        vis[x][y][2] = 1;
                    } else break;
                }
            } else if (op == 'D') {
                int x = tx + 1, y = ty;
                if (vis[x][y][mp[x][y]] == 1) {
                    break;
                } else {
                    if (mp[x][y] == 0) {
                        tx = x; ty = y;
                        vis[x][y][0] = 1;
                    } else if (mp[x][y] == 2) {
                        tx = x; ty = y;
                        vis[x][y][2] = 1;
                    } else break;
                }
            } else if (op == 'L') {
                int x = tx, y = ty - 1;
                if (vis[x][y][mp[x][y]] == 1) {
                    break;
                } else {
                    if (mp[x][y] == 0) {
                        tx = x; ty = y;
                        vis[x][y][0] = 1;
                    } else if (mp[x][y] == 2) {
                        tx = x; ty = y;
                        vis[x][y][2] = 1;
                    } else break;
                }
            } else if (op == 'R') {
                int x = tx, y = ty + 1;
                if (vis[x][y][mp[x][y]] == 1) {
                    break;
                } else {
                    if (mp[x][y] == 0) {
                        tx = x; ty = y;
                        vis[x][y][0] = 1;
                    } else if (mp[x][y] == 2) {
                        tx = x; ty = y;
                        vis[x][y][2] = 1;
                    } else break;
                }
            } else if (op == 'P') {
                if (mp[tx][ty] == 2) {
                    ans++; 
                    mp[tx][ty] = 0;
                    // vis[tx][ty][0] = 1;
                } else break;
            } else if (op == 'I') {
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}