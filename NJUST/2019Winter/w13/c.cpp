#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int dir[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

map<int,map<int,int>> mp, dis;
PII st, ed;
int n;

int main() {
    scanf("%d%d%d%d%d", &st.first, &st.second, &ed.first, &ed.second, &n);
    for (int i = 1, r, a, b; i <= n; i++) {
        scanf("%d%d%d", &r, &a, &b);
        for (int i = a; i <= b; i++) mp[r][i] = 1;
    }
    queue<PII> q; q.push(st); dis[st.first][st.second] = 0;
    while (!q.empty()) {
        PII u = q.front(); q.pop();
        if (u == ed) return printf("%d\n", dis[ed.first][ed.second]), 0;
        for (int i = 0; i < 8; i++) {
            int x = u.first + dir[i][0], y = u.second + dir[i][1];
            // if (x < 1 || y < 1 || x > 1e9 || y > 1e9) continue;
            if (mp[x][y]) {
                if (dis.count(x) && dis[x].count(y)) continue;
                dis[x][y] = dis[u.first][u.second] + 1;
                q.push({x, y});
            }
        }
    }
    puts("-1");
    return 0;
}