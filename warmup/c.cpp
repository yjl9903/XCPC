#include <bits/stdc++.h>
#define ms(a, b) memset(a, b, sizeof a)
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
const int maxn = 5e5 + 10;

struct pam {
    int sz, tot, last;
    int ch[maxn][26], len[maxn], fail[maxn];
    int pos[maxn];
    char s[maxn];
    int node(int l) {
        sz++; ms(ch[sz], 0);
        len[sz] = l; fail[sz] = pos[sz] = 0;
        return sz;
    }
    void clear() {
        sz = -1; last = 0;
        s[tot = 0] = '$';
        node(0); node(-1);
        fail[0] = 1;
    }
    int getfail(int x) {
        while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
        return x;
    }
    void insert(char c, int i) {
        s[++tot] = c;
        int now = getfail(last);
        if (!ch[now][c - 'a']) {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail(fail[now])][c - 'a'];
            ch[now][c - 'a'] = x;
            pos[x] = i;
        }
        last = ch[now][c - 'a'];
    }
    void print() {
      for (int i = 0; i < sz; i++) {
        dbg(i, ch[i][0], ch[i][1], ch[i][2]);
      }
    }
} f, g;

int n;
char s[maxn], t[maxn];

int ans, l1, l2;
void dfs(int a, int b, int d) {
    if (d > ans) {
        ans = d;
        l1 = f.pos[a];
        l2 = g.pos[b];
    }
    for (int i = 0; i < 4; i++) {
      // dbg(a, b, i);
        if (f.ch[a][i] && g.ch[b][i]) {
            dfs(f.ch[a][i], g.ch[b][i], d + 1);
        }
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        f.clear(); g.clear();
        scanf("%d%s%s", &n, s + 1, t + 1);
        for (int i = 1; i <= n; i++) {
            f.insert(s[i], i);
            g.insert(t[i], i);
        }
        f.print();
        g.print();
        ans = 0;
        dfs(1, 1, 0);
        dfs(0, 0, 0);
        if (ans == 0) {
            puts("0");
        } else {
            printf("%d\n%d %d\n%d %d\n", ans, l1 - ans + 1, l1, l2 - ans + 1, l2);
        }
    }
    return 0;
}