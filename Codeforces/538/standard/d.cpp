#include <bits/stdc++.h>

#define N 5020

using namespace std;

int n, c[N], f[N][N], g[N][N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
	memset(f, 63, sizeof(f));
	memset(g, 63, sizeof(g));
	for (int i = 1; i <= n; ++i) f[i][i] = g[i][i] = 0;
	for (int itv = 0; itv < n; ++itv) {
		for (int i = 1; i + itv <= n; ++i) {
			int j = i + itv;
			if (i - 1 >= 1) {
				f[i - 1][j] = min(f[i - 1][j], f[i][j] + (c[i - 1] != c[i]));
				f[i - 1][j] = min(f[i - 1][j], g[i][j] + (c[i - 1] != c[j]));
			}
			if (j + 1 <= n) {
				g[i][j + 1] = min(g[i][j + 1], f[i][j] + (c[i] != c[j + 1]));
				g[i][j + 1] = min(g[i][j + 1], g[i][j] + (c[j] != c[j + 1]));
			}
		}
	}
	printf("%d\n", min(f[1][n], g[1][n]));
}