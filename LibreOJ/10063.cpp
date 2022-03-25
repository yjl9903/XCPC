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
const int mod = 10007;
const int inf = 1 << 30;
const int maxn = 6000 + 5;

namespace ACAM {
    static const int maxp = 10000 + 5;
    int sz, ch[maxp][26], fail[maxp];
    int danger[maxp];
    int node() {
        ms(ch[++sz], 0); 
        fail[sz] = 0; danger[sz] = 0;
        return sz;
    }
    void clear() {
        sz = 0; node();
        for (int i = 0; i < 26; i++) ch[0][i] = 1;
    }
    void insert(char* s, int i) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            int v = s[i] - 'A';
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        danger[u] = 1;
    }
    void build() {
        queue<int> q; q.push(1);
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
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

int n, m;
int dp[200][maxp];
char s[maxn];

int main() {
    clear();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s); insert(s, i);
    }
    build();
    auto add = [](int& a, int b) {
        a += b; if (a >= mod) a -= mod;
    };
    dp[0][1] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= sz; j++) {
            for (int v = 0; v < 26; v++) {
                if (danger[ch[j][v]]) continue;
                int nx = ch[j][v];
                add(dp[i][nx], dp[i - 1][j]);
            }
        }
    }
    int ans = 1;
    for (int i = 1; i <= m; i++) ans = ans * 26ll % mod;
    for (int i = 1; i <= sz; i++) add(ans, mod - dp[m][i]);
    cout << ans;
    return 0;
}