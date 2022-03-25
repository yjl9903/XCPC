#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 10 + 5;
const int inf = 1e5 + 7;

int a[maxn][maxn], n, r = 1 << 30, r2 = 1 << 30;
PII loc[maxn * maxn];
int dir[8][2] = {1, 2, 2, 1, -1, 2, 2, -1, 1, -2, -2, 1, -1, -2, -2, -1};
int dis[maxn * maxn][3];
PII dp[maxn * maxn][3];

bool vis[maxn][maxn]; int d[maxn][maxn];
int bfs(PII s, PII t){
    ms(vis, 0); vis[s.first][s.second] = 1; d[s.first][s.second] = 0;
    queue<PII> q; q.push(s);
    while (!q.empty()){
        PII x = q.front(); q.pop();
        if (x == t) return d[x.first][x.second];
        for (int i = 0; i < 8; i++){
            int tx = x.first + dir[i][0];
            int ty = x.second + dir[i][1];
            if (tx < 1 || ty < 1 || tx > n || ty > n) continue;
            if (vis[tx][ty]) continue;
            d[tx][ty] = d[x.first][x.second] + 1; 
            vis[tx][ty] = 1; q.emplace(tx, ty);
        }
    }
    return inf;
}
int bfs2(PII s, PII t){
    for (int i = 1; i <= n; i++){
        for (int s1 = 0; s1 < 4; s1++){
            PII x = s;
            if (s1 & 1) x.first += i;
            else x.first -= i;
            if ((s1 >> 1) & 1) x.second += i;
            else x.second -= i;
            if (x.first < 1 || x.second < 1 || x.first > n || x.second > n) continue;
            if (x == t) return 1;
            for (int j = 1; j <= n; j++){
                for (int s2 = 0; s2 < 4; s2++){
                    PII x2 = x;
                    if (s2 & 1) x2.first += j;
                    else x2.first -= j;
                    if ((s2 >> 1) & 1) x2.second += j;
                    else x2.second -= j;
                    if (x2.first < 1 || x2.second < 1 || x2.first > n || x2.second > n) continue;
                    if (x2 == t) return 2;
                }
            }
        }
    }
    return inf;
}

PII cmp(PII a, PII b){
    if (a.first < b.first) return a;
    if (a.first > b.first) return b;
    if (a.second < b.second) return a;
    else return b;
}
PII cmp(PII a, PII b, PII c){
    return cmp(a, cmp(b, c));
}
PII add(PII a, int b, int c = 0){
    return make_pair(a.first + b + c, a.second + c);
}

int main(){
    scanf("%d", &n); int tx, ty;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        scanf("%d", &a[i][j]);
        loc[a[i][j]] = make_pair(i, j);
    }
    for (int i = 1; i < n * n; i++){
        PII s = loc[i], t = loc[i + 1];

        dis[i][0] = bfs(s, t);

        if (s.first != t.first && s.second != t.second) dis[i][1] = 2;
        else dis[i][1] = 1;

        // if (abs(s.first - t.first) == abs(s.second - t.second)) dis[i][2] = 1;
        // else dis[i][2] = 2;
        dis[i][2] = bfs2(s, t);

        dbg(dis[i][0], dis[i][1], dis[i][2]);
    }
    dp[1][0] = dp[1][1] = dp[1][2] = make_pair(0, 0);
    for (int i = 2; i <= n * n; i++){
        if (dis[i - 1][0] < inf) 
            dp[i][0] = cmp(add(dp[i - 1][0], dis[i - 1][0]), add(dp[i - 1][1], dis[i - 1][0], 1), add(dp[i - 1][2], dis[i - 1][0], 1));
        else dp[i][0] = make_pair(inf, inf);
        if (dis[i - 1][2] < inf)
            dp[i][2] = cmp(add(dp[i - 1][0], dis[i - 1][2], 1), add(dp[i - 1][1], dis[i - 1][2], 1), add(dp[i - 1][2], dis[i - 1][2]));
        else dp[i][2] = make_pair(inf, inf);
        dp[i][1] = cmp(add(dp[i - 1][0], dis[i - 1][1], 1), add(dp[i - 1][1], dis[i - 1][1]), add(dp[i - 1][2], dis[i - 1][1], 1));

        dbg(dis[i - 1][0], dis[i - 1][1], dis[i - 1][2]);
        dbg(dp[i][0].first, dp[i][0].second, dp[i][1].first, dp[i][1].second, dp[i][2].first, dp[i][2].second);
    }
    PII ans = cmp(dp[n * n][0], dp[n * n][1], dp[n * n][2]);
    cout << ans.first << ' ' << ans.second;
    return 0;
}