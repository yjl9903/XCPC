#include <bits/stdc++.h>
using namespace std;
 
#define MAX_N 200010
 
int N, D, deg[MAX_N], used[MAX_N], dep[MAX_N], par[MAX_N];
vector<int> adj[MAX_N];
vector<int> atDepth[MAX_N];
 
vector<int> ans;
 
void dfs(int p, int i, int d) {
    par[i] = p;
    dep[i] = d;
    atDepth[d].push_back(i);
    for (int j : adj[i])
        if (j != p) {
            dfs(i, j, d + 1);
        }
}
 
bool mark(int p, int d) {
    if (p == -1 || d == 0) return true;
    if (D - d < used[p]) return false;
    used[p] = d;
    return mark(par[p], d - 1);
}
 
int main() {
    ios_base::sync_with_stdio(false);
 
    cin >> N >> D;
 
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }
 
    dfs(-1, 1, 0);
 
    for (int d = N; d >= 0; d--) {
        for (int i : atDepth[d]) {
            if (mark(i, D))
                ans.push_back(i);
        }
    }
 
    cout << ans.size() << "\n";
    for (int i : ans) cout << i << " ";
    cout << "\n";
 
    return 0;
}