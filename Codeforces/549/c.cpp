#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, rt, fa[maxn], key[maxn], siz[maxn], vis[maxn];

void dfs(int u) {
    for (int& v: edge[u]) {
        siz[u] += key[v];
        dfs(v);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", fa + i, key + i);
        key[i] ^= 1;
        if (fa[i] == -1) rt = i;
        else {
            edge[fa[i]].push_back(i);
        }
    }
    dfs(rt);
    vector<int> ans; set<int> st;
    for (int i = 1; i <= n; i++) if (siz[i] == 0 && key[i] == 0) st.insert(i);
    // for (int i = 1; i <= n; i++)  cout << siz[i] << endl;
    while (!st.empty()) {
        auto it = st.begin();
        if (*it == rt) break;
        ans.push_back(*it);
        vis[*it] = 1;
        siz[fa[*it]] -= key[*it];
        if (fa[*it] != -1) {
            if (key[fa[*it]] == 0 && !vis[fa[*it]] && siz[fa[*it]] == 0) st.insert(fa[*it]);
        }
        st.erase(it);
    }
    if (ans.empty()) puts("-1");
    else {
        for (int& x: ans) printf("%d ", x);
    }
    return 0;
}