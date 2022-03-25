#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 2000 + 5;

int n, m, pre[maxn], G[maxn][maxn], deg[maxn], ans[maxn];
char tmp[maxn];
vector<int> block[maxn], edge[maxn];

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n + m; i++) pre[i] = i;
    for (int i = 1; i <= n; i++) {
        scanf("%s", tmp + 1);
        for (int j = 1; j <= m; j++) {
            if (tmp[j] == '<') G[i][j + n] = 1;
            else if (tmp[j] == '>') G[j + n][i] = 1;
            else {
                int x = find(i), y = find(j + n);
                pre[x] = y;
            }
        }
    }
    for (int i = 1; i <= n + m; i++) block[find(i)].push_back(i);
    int k = 0;
    for (int i = 1; i <= n + m; i++) {
        if (block[i].empty()) continue;
        k++; 
        // for (int& x: block[i]) bel[x] = k;
        for (int k = 0; k < block[i].size(); k++) {
            for (int j = k + 1; j < block[i].size(); j++) {
                int u = block[i][j], v = block[i][k];
                if (G[u][v] || G[v][u]) return puts("No"), 0;
            }
        }
    }
    dbg(k);
    for (int i = 1; i <= n + m; i++) for (int j = 1; j <= n + m; j++) {
        if (G[i][j]) {
            edge[find(i)].push_back(find(j));
            deg[find(j)]++;
        }
    } 
    vector<int> v;
    // for (int i = 1; i <= k; i++) if (deg[i] == 0) ans[i] = 1, v.push_back(i); 
    int cnt = 0;
    for (int i = 1; i <= n + m; i++) if (pre[i] == i && deg[i] == 0) ans[i] = 1, v.push_back(i);
    while (!v.empty()) {
        int tp = v.back(); v.pop_back();
        for (int& x: edge[tp]) {
            deg[x]--; 
            if (deg[x] == 0) ans[x] = ans[tp] + 1, v.push_back(x);
        }
        cnt++;
    }
    if (cnt < k) return puts("No"), 0;
    puts("Yes");
    for (int i = 1; i <= n + m; i++) printf("%d%c", ans[find(i)], " \n"[i == n]);
    return 0;
}