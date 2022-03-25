#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
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
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace ACAM {
    static const int maxp = 500000 + 5;
    int sz, ch[maxp][26], fail[maxp];
    int danger[maxp];
    int node() {
        ms(ch[++sz], 0); 
        fail[sz] = 0; danger[sz] = 0;
        return sz;
    }
    void clear() {
        sz = 0; node();
        for (int i = 0; i < 2; i++) ch[0][i] = 1;
    }
    void insert(char* s, int i) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            int v = s[i] - '0';
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        danger[u] = 1;
    }
    void build() {
        queue<int> q; q.push(1);
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 0; i < 2; i++) {
                if (ch[t][i]) {
                    fail[ch[t][i]] = ch[fail[t]][i];
                    danger[ch[t][i]] |= danger[fail[ch[t][i]]];
                    q.push(ch[t][i]);
                } else {
                    ch[t][i] = ch[fail[t]][i];
                }
            }
        }
    }
} using namespace ACAM;

int n;
char s[maxn];

int vis[maxn], ok[maxn], flag = 0;
void dfs(int u) {
    if (flag) return ;
    if (vis[u]) {
        flag = 1; return ;
    }
    if (danger[u] || ok[u]) return ;
    vis[u] = ok[u] = 1;
    dfs(ch[u][0]); 
    dfs(ch[u][1]);
    vis[u] = 0;
}

int main() {
    clear();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s); insert(s, i);
    }
    build();
    dfs(1);
    if (!flag) puts("NIE");
    else puts("TAK");
    return 0;
}