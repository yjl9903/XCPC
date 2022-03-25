#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <unordered_map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1e9 + 7;
const int maxn = 500000 + 50;

vector<PII> edge[maxn];
int n;

int siz[maxn], son[maxn], dep[maxn];
void getsz(int u) {
    siz[u] = 1; int m = -1;
    for (auto& x: edge[u]) {
        int v = x.first;
        dep[v] = dep[u] + 1;
        getsz(v); siz[u] += siz[v];
        if (siz[v] > m) m = siz[v], son[u] = v;
    }
}

int offset, ans[maxn];
int mp[(1 << 22) + 5], tmp[(1 << 22) + 5];
int query(int x) {
    int ans = mp[x ^ offset];
    for (int i = 0; i < 22; i++) {
        ans = max(ans, mp[x ^ (1 << i) ^ offset]);
    }
    return ans;
}
vector<int> vec;
void add(int u, int val, int x) {
    if (x == 1) {
        vec.push_back(val);
        tmp[val] = max(tmp[val], dep[u]);
    } else if (x == 2) {
        tmp[val] = -inf;
    } else {
        mp[val ^ offset] = -inf;
    }
    for (auto& v: edge[u]) {
        add(v.first, val ^ v.second, x);
    }
}
void dfs(int u, int kp) {
    int val = 0;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == son[u]) {
            val = x.second; continue;
        }
        dfs(v, 0);
    }
    if (son[u]) {
        // dbg(u, son[u], val);
        dfs(son[u], 1);

        mp[offset] = max(mp[offset], dep[son[u]]);
        offset ^= val;

        ans[u] = max(1, query(0) - dep[u]);
        // dbg(1, u, ans[u]);
        for (auto& x: edge[u]) {
            int v = x.first; 
            if (v == son[u]) continue;
            vec.clear();
            add(v, x.second, 1);
            for (int& info: vec) {
                ans[u] = max(ans[u], query(info) + tmp[info] - 2 * dep[u]);
            }
            for (int& info: vec) {
                mp[info ^ offset] = max(mp[info ^ offset], tmp[info]);
            }
            ans[u] = max(ans[u], query(0) - dep[u]);
            add(v, x.second, 2);
        }
    }
    if (!kp) {
        add(u, 0, -1);
        offset ^= val;
    }
}

void dfs2(int u) {
    for (auto& x: edge[u]) {
        dfs2(x.first); ans[u] = max(ans[u], ans[x.first]);
    }
}

int main() {
    for (int i = 0; i < (1 << 22); i++) tmp[i] = mp[i] = -inf;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        int x; char ch[2];
        scanf("%d%s", &x, ch); edge[x].push_back({i, 1 << (ch[0] - 'a')});
    } dep[1] = 1; getsz(1);
    dfs(1, 1); dfs2(1);
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}