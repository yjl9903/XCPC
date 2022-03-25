#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <string>
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
const int maxn = 200000 + 5;

namespace ACAM {
    vector<int> edge[maxn];
    static const int maxp = 200000 + 5;
    int sz, ch[maxp][26], fail[maxp];
    ll val[maxp];
    int node() {
        ms(ch[++sz], 0); fail[sz] = 0; val[sz] = 0;
        return sz;
    }
    void clear() {
        sz = 0; node();
        for (int i = 0; i < 26; i++) ch[0][i] = 1;
    }
    void insert(const char* s, int i) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            int v = s[i] - 'a';
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        val[u]++;
    }
    void dfs(int u) {
        for (int v: edge[u]) {
            val[v] += val[u];
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
        for (int i = 0; i <= sz; i++) edge[i].clear();
        for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
        dfs(1);
    }
}
using namespace ACAM;

char s[maxn], t[maxn];
int n;
ll ed[maxn], st[maxn];
string str[maxn];

int main() {
    ACAM::clear();
    scanf("%s%d", s + 1, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", t);
        str[i] = string(t);
        ACAM::insert(t, i);
    }
    ACAM::build();
    int slen = strlen(s + 1), u = 1;
    for (int i = 1; i <= slen; i++) {
        int c = s[i] - 'a';
        u = ch[u][c];
        ed[i] = val[u];
    }
    // for (int i = 1; i <= slen; i++) dbg(i, ed[i]);
    ACAM::clear();
    for (int i = 1; i <= n; i++) {
        reverse(str[i].begin(), str[i].end());
        ACAM::insert(str[i].c_str(), i);
    }
    ACAM::build();
    u = 1;
    for (int i = slen; i >= 1; i--) {
        int c = s[i] - 'a';
        u = ch[u][c];
        st[i] = val[u];
    }
    // for (int i = 1; i <= slen; i++) dbg(i, st[i], ed[i]);
    ll ans = 0;
    for (int i = 1; i < slen; i++) ans += ed[i] * st[i + 1];
    cout << ans;
    return 0;
}