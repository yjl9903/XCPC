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
const int maxn = 1000000 + 5;

struct ACAM {
    static const int maxp = 500000 + 5;
    int sz, ch[maxp][26], fail[maxp];
    int siz[maxp];
    void clear() {
        sz = 0; node();
        for (int i = 0; i < 26; i++) ch[0][i] = 1;
    }
    int node() {
        ms(ch[++sz], 0); fail[sz] = 0; siz[sz] = 0;
        return sz;
    }
    ACAM() { clear(); }
    void insert(char* s, int i) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            int v = s[i] - 'a';
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        siz[u]++;
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
    int query(char* s) {
        int ans = 0;
        for (int i = 0, u = 1; s[i]; i++) {
            u = ch[u][s[i] - 'a'];
            int p = u;
            while (p > 1 && siz[p] != -1) {
                ans += siz[p];
                siz[p] = -1;
                p = fail[p];
            }
        }
        return ans;
    }
} f;

int n; char s[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        f.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%s", s); f.insert(s, i);
        }
        f.build();
        scanf("%s", s);
        printf("%d\n", f.query(s));
    }
    return 0;
}