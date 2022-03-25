#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500000 + 5;

vector<int> edge[maxn];
set<int> que[maxn];
map<int,int> ans[maxn];
char s[maxn];
int n, q, v[maxn], h[maxn];

int sz[maxn], son[maxn], dep[maxn];
void getsz(int u, int f){
    sz[u] = 1; dep[u] = dep[f] + 1;
    for (auto& v : edge[u]){
        if (v == f) continue;
        getsz(v, u); sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

int sk[maxn], cnt[maxn][30];
bool check(int d){
    int flag = 0;
    for (int i = 0; i < 26; i++){
        if (cnt[d][i] & 1) flag++;
    }
    return flag <= 1;
}
void add(int u, int f, int x){
    cnt[dep[u]][s[u] - 'a'] += x;
    for (auto& v : edge[u]){
        if (v == f || sk[v]) continue;
        add(v, u, x);
    }
}
void dfs(int u, int f, int kp){
    for (auto& v : edge[u]){
        if (v == f || v == son[u]) continue;
        dfs(v, u, 0);
    }
    if (son[u]) dfs(son[u], u, 1), sk[son[u]] = 1;
    add(u, f, 1); sk[son[u]] = 0;

    for (auto& x : que[u]){
        if (check(x)) ans[u][x] = 1;
    }

    if (!kp) add(u, f, -1);
}

int main(){
    scanf("%d%d", &n, &q);
    for (int i = 2, x; i <= n; i++) scanf("%d", &x), edge[x].push_back(i);
    scanf("%s", s + 1);
    for (int i = 1; i <= q; i++){
        scanf("%d%d", v + i, h + i);
        que[v[i]].insert(h[i]);
    }
    getsz(1, 0); dfs(1, 0, 1);
    for (int i = 1; i <= q; i++){
        // printf("%d\n", ans[v[i]][h[i]]);
        if (ans[v[i]][h[i]]) puts("Yes");
        else puts("No");
    }
    return 0;
}