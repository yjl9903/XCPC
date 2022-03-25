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
const int maxn = 2000000 + 5;

struct ACAM {
    static const int maxp = 2000000 + 5;
    int sz, ch[maxp][26], fail[maxp];
    void clear() {
        sz = 1;
        for (int i = 0; i < 26; i++) ch[0][i] = 1;
    }
    int node() {
        sz++; 
        ms(ch[sz], 0); fail[sz] = 0;
        return sz;
    }
    ACAM() { clear(); }
    int match[300];
    void insert(char* s, int i) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            int v = s[i] - 'a';
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        match[i] = u;
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
    }
    int siz[maxp];
    vector<int> edge[maxp];
    void dfs(int u) {
        for (int v: edge[u]) {
            dfs(v); siz[u] += siz[v];
        }
    }
    vector<int> solve(int n) {
        for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
        dfs(1); vector<int> cnt;
        for (int i = 1; i <= n; i++) {
            // dbg(match[i], siz[match[i]]);
            cnt.push_back(siz[match[i]]);
        }
        return cnt;
    }
} f;

int n;
char s[maxn];

int main() {
    scanf("%d", &n);
    int len = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + len);
        f.insert(s + len, i);
        len += strlen(s + len);
        s[len] = '#'; len++;
    }
    f.build();
    // for (int i = 0; i < len; i++) putchar(s[i]);
    for (int i = 0, u = 1; i < len; i++) {
        if (s[i] == '#') {
            u = 1;
        } else {
            u = f.ch[u][s[i] - 'a'];
            f.siz[u]++;
        }
    }
    vector<int> ans = f.solve(n);
    for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
    return 0;
}