#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000 + 5;

map<int,int> mp; int id;
int gid(int x) {
    if (mp.count(x)) return mp[x];
    else return mp[x] = ++id;
}
int n, s;
vector<int> edge[maxn];

int nxt[maxn], vis[maxn];
int dfs(int u) {
    for (int v: edge[u]) {
        if (vis[v]) continue;
        vis[v] = 1;
        if (nxt[v] == -1 || dfs(nxt[v])) {
            nxt[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        mp.clear(); id = 0;
        scanf("%d%d", &n, &s);
        int l = max(n + 1, s + 1);
        int r = s + n;
        printf("Case #%d: ", ++kase);
        if (r - l + 1 >= 400) {
            puts("No"); continue;
        }
        for (int i = l; i <= r; i++) {
            for (int j = 1; j <= r - l + 1; j++) {
                if (i % j) continue;
                edge[gid(i)].push_back(gid(j));
                edge[gid(j)].push_back(gid(i));
            }
        }
        int c = 0;
        ms(nxt, -1);
        for (int i = 1; i <= r - l + 1; i++) {
            ms(vis, 0);
            if (dfs(gid(i))) c++;
        }
        if (c == r - l + 1) puts("Yes");
        else puts("No");
        for (int i = 0; i <= id; i++) edge[i].clear();
    }
    return 0;
}