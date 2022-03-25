#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

namespace acam {
    static const int maxp = 300000 + 5;
    int sz, ch[maxp][26], fail[maxp];
    int len[maxp];
    int node() {
        ms(ch[++sz], 0); fail[sz] = 0;
        len[sz] = 0;
        return sz;
    }
    void clear() {
        sz = 0; node();
        for (int i = 0; i < 26; i++) ch[0][i] = 1;
    }
    int insert(char* s) {
        int i, u = 1;
        for (i = 0; s[i]; i++) {
            int v = s[i] - 'a';
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        len[u] = i;
        return u;
    }
    vector<int> edge[maxp];
    void dfs(int u) {
        for (int v: edge[u]) {
            len[v] = max(len[v], len[u]);
            dfs(v);
        }
    }
    void build() {
        queue<int> q; q.push(1);
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
                if (ch[t][i]) {
                    fail[ch[t][i]] = ch[fail[t]][i];
                    q.push(ch[t][i]);
                } else {
                    ch[t][i] = ch[fail[t]][i];
                }
            }
        }
        for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
        dfs(1);
    }
}
using acam::ch;
using acam::len;

int n, L, dp[maxn];
char s[maxn], tmp[maxn];

int a[maxn << 2];
void build(int l = 0, int r = n, int rt = 1) {
    for (int i = l; i <= r; i++) a[i] = inf;
}
void update(int p, int x, int l = 0, int r = n, int rt = 1) {
    a[p] = x;
}
int query(int L, int R, int l = 0, int r = n, int rt = 1) {
    int ans = inf;
    for (int i = L; i <= R; i++) ans = min(ans, a[i]);
    return ans;
}

int main() {
    acam::clear();
    scanf("%d%s", &L, s + 1);
    n = strlen(s + 1);
    build(); update(0, 0);
    for (int i = 1; i <= L; i++) {
        scanf("%s", tmp);
        acam::insert(tmp);
    }
    acam::build();
    int u = 1;
    for (int i = 1; i <= n; i++) {
        int c = s[i] - 'a';
        if (ch[u][c] == 0) return puts("-1"), 0;
        u = ch[u][c];
        if (len[u] >= 1) {
            int tot = 1 + query(i - len[u], i - 1);
            update(i, tot);
        }
    }
    int ans = query(n, n);
    // if (ans < inf) {
    //     cout << ans;
    // } else {
    //     puts("-1");
    // }
    cout << ans;
    return 0;
}