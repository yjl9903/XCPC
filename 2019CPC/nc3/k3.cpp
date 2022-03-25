#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<stack>
#include<utility>
using namespace std;

namespace NoRotateTreap {

	const int maxn = 1e7;

	struct node {
		int value, key, Size, child[2];
	}arr[maxn + 5];

	int tot;

	inline void Push_Up(int index) {
		arr[index].Size = arr[arr[index].child[0]].Size + arr[arr[index].child[1]].Size + 1;
	}

	void Split(int root, int& a, int& b, int value) {
		if (!root) {
			a = b = 0;
			return;
		}
		if (arr[root].value <= value)a = root, Split(arr[root].child[1], arr[a].child[1], b, value);
		else b = root, Split(arr[root].child[0], a, arr[b].child[0], value);
		Push_Up(root);
	}

	void Merge(int& root, int a, int b) {
		if (!a || !b) {
			root = a + b;
			return;
		}
		if (arr[a].key < arr[b].key)root = a, Merge(arr[root].child[1], arr[a].child[1], b);
		else root = b, Merge(arr[root].child[0], a, arr[b].child[0]);
		Push_Up(root);
	}

	inline void Insert(int& root, int value) {
		int x = 0, y = 0, z = ++tot;
		arr[z].value = value, arr[z].key = rand(), arr[z].Size = 1;
		Split(root, x, y, value);
		Merge(x, x, z);
		Merge(root, x, y);
	}

	inline void Erase(int& root, int value) {
		int x = 0, y = 0, z = 0;
		Split(root, x, y, value);
		Split(x, x, z, value - 1);
		Merge(z, arr[z].child[0], arr[z].child[1]);
		Merge(x, x, z);
		Merge(root, x, y);
	}

	int Get_Rank(int& root, int value) {
		int x = 0, y = 0;
		Split(root, x, y, value);
		int res = arr[x].Size;
		Merge(root, x, y);
		return res;
	}

}

typedef long long ll;
const int maxm = 1e5;
int root[maxm + 5];
int n, k, val[maxm + 5];
ll res;

namespace DsuOnTree {

	const int maxn = 1e5;

	typedef pair<int, int> pii;

	vector<int> g[maxn + 5];
	int son[maxn + 5], sz[maxn + 5], deep[maxn + 5], parent[maxn + 5];
	bool vis[maxn + 5];
	stack<pii> sta;
	
	void add(int u, int type) {
		if (type == 1)NoRotateTreap::Insert(root[val[u]], deep[u]);
		if (type == -1)NoRotateTreap::Erase(root[val[u]], deep[u]);
		for (int i = 0; i < g[u].size(); ++i) {
			int v = g[u][i];
			if (v == parent[u] || vis[v])continue;
			add(v, type);
		}
	}

	void query(int u, int lca) {
		int value = 2 * val[lca] - val[u];
		int d = k + 2 * deep[lca] - deep[u];
		if (value >= 0 && value <= n && d > 0)res += NoRotateTreap::Get_Rank(root[value], d);
		for (int i = 0; i < g[u].size(); ++i) {
			int v = g[u][i];
			if (v == parent[u])continue;
			query(v, lca);
		}
	}

	void dfs1(int u, int father) {
		deep[u] = deep[father] + 1, parent[u] = father, sz[u] = 1;
		for (int i = 0; i < g[u].size(); ++i) {
			int v = g[u][i];
			if (v == father)continue;
			dfs1(v, u);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[v] > sz[son[u]])son[u] = v;
		}
	}

	void dfs2(int u, int opt) {
		for (int i = 0; i < g[u].size(); ++i) {
			int v = g[u][i];
			if (v == parent[u] || v == son[u])continue;
			dfs2(v, 0);
		}
		if (son[u] != -1)dfs2(son[u], 1), vis[son[u]] = true;
		for (int i = 0; i < g[u].size(); ++i) {
			int v = g[u][i];
			if (v == parent[u] || vis[v])continue;
			query(v, u);
			add(v, 1);
		}
		NoRotateTreap::Insert(root[val[u]], deep[u]);
		if (son[u] != -1)vis[son[u]] = false;
		if (!opt) {
			for (int i = 0; i < g[u].size(); ++i) {
				int v = g[u][i];
				if (v == parent[u] || vis[v])continue;
				add(v, -1);
			}
			NoRotateTreap::Erase(root[val[u]], deep[u]);
		}
	}
}

int read_int() {
	char c;
	int ret = 0, sgn = 1;
	do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
	if (c == '-') sgn = -1; else ret = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
	return sgn * ret;
}

int main()
{
	srand(19260817);
	n = read_int(), k = read_int();
	for (int i = 1; i <= n; ++i)val[i] = read_int();
	for (int i = 2, x; i <= n; ++i) {
		x = read_int();
		DsuOnTree::g[i].push_back(x);
		DsuOnTree::g[x].push_back(i);
	}
	memset(DsuOnTree::son, -1, sizeof(DsuOnTree::son));
	DsuOnTree::dfs1(1, 0);
	DsuOnTree::dfs2(1, 1);
	printf("%lld\n", 2 * res);
	return 0;
}