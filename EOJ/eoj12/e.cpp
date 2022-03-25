#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 200000 + 5;

vector<int> edge[maxn];
int n, k, tag, key[maxn];

int dfs(int u, int f) {
    int sum = 1, mx = 0;
    if (key[u]) mx = tag;
    for (int& v: edge[u]) {
        if (v == f) continue;
        int x = dfs(v, u);
        if (x < 0) {
            sum += -x;
        } else if (x > 0) {
            mx = max(mx, x);
        }
    }
    if (mx >= sum) return mx - sum;
    return -sum;
}
int check(int x) {
    tag = x;
    return dfs(1, 0) >= 0;
}

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = 1, x; i <= k; i++) {
        scanf("%d", &x); key[x] = 1;
    }
    int l = 0, r = maxn, ans = 0;
    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) r = m - 1, ans = m;
        else l = m + 1;
    }
    printf("%d", ans);
    return 0;
}