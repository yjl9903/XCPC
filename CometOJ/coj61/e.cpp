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
const int maxn = 15 + 5;

int n, vis[maxn][maxn];
char s[maxn][maxn];
int dir[4][2] = { 0, 1, -1, 0, 0, -1, 1, 0 };

string get(int d, int x, int y) {
    if (d == 0 && s[x + 1][y] == '#') return "D";
    if (d == 1 && s[x][y + 1] == '#') return "R";
    if (d == 2 && s[x - 1][y] == '#') return "U";
    if (d == 3 && s[x][y - 1] == '#') return "L"; 
    return "";
}

int main() {
    scanf("%d", &n);
    int sx, sy, tx, ty, d = 0;
    for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        if (s[i][j] == 'S') sx = i, sy = j;
        if (s[i][j] == 'T') tx = i, ty = j;
    }
    // dbg(sx, sy, tx, ty);
    string ans("D");
    while (true) {
        vis[sx][sy] = 1;
        int td = d;
        for (int t = 0; t < 4; t++) {
            // int x = sx + dir[d][0], y = sy + dir[d][1];
            int x = sx + dir[t][0], y = sy + dir[t][1];

            if (s[x][y] == '#' || vis[x][y]) {
                d = (d + 1) % 4;
            } else {
                // if (t > 0) {
                //     ans += get(t, sx, sy);
                // }
                d = t;
                sx = x; sy = y; break;
            }
        }
        ans += get(d, sx, sy);
        dbg(d, sx, sy, ans);
        if (sx == tx && sy == ty) {
            break;
        }
    }
    cout << ans;
    return 0;
}