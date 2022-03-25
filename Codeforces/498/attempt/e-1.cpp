#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5;

int n, q;
int in[MAX_N + 1], out[MAX_N + 1], dfsTime;
vector<int> adj[MAX_N + 1];
int ver[MAX_N + 1];

void dfs(int u, int fa) {
	in[u] = ++dfsTime;
	ver[in[u]] = u;
	for (int v : adj[u]) {
		if (v == fa) continue;
		dfs(v, u);
	}
	out[u] = dfsTime;
}

int main() {
	//freopen("input.inp", "r", stdin);
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for (int i = 2; i <= n; ++i) {
		int p; cin >> p;
		adj[p].push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		sort(adj[i].begin(), adj[i].end());
	}
	dfsTime = 0;
	dfs(1, 1);
	while (q--) {
		int u, k; cin >> u >> k;
		if (k > out[u] - in[u] + 1) {
			cout << -1 << '\n';
		} else {
			cout << ver[in[u] + k - 1] << '\n';
		}
	}
	return 0;
}