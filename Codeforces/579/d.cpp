#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
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

char s[maxn], t[maxn];
int slen, tlen, nxt[maxn][26], pre[maxn], suf[maxn];

int main() {
    scanf("%s%s", s + 1, t + 1);
    slen = strlen(s + 1);
    tlen = strlen(t + 1);
    for (int i = 0; i < 26; i++) nxt[slen][i] = nxt[slen + 1][i] = slen + 1;
    for (int i = slen - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
        nxt[i][s[i + 1] - 'a'] = i + 1;
    }
    int u = 0;
    for (int i = 1; i <= tlen; i++) {
        int c = t[i] - 'a';
        if (nxt[u][c] == slen + 1) return puts("0"), 0;
        u = nxt[u][c];
        pre[i] = u;
    }
    reverse(s + 1, s + slen + 1);
    reverse(t + 1, t + tlen + 1);
    for (int i = slen - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
        nxt[i][s[i + 1] - 'a'] = i + 1;
    }
    suf[tlen + 1] = slen + 1;
    u = 0; 
    for (int i = 1; i <= tlen; i++) {
        int c = t[i] - 'a';
        // if (!nxt[u][c]) return puts("0"), 0;
        assert(nxt[u][c] != slen + 1);
        u = nxt[u][c];
        suf[tlen - i + 1] = slen - u + 1;
    }
    int ans = 0;
    for (int i = 0; i <= tlen; i++) {
        dbg(i, suf[i + 1], pre[i]);
        ans = max(ans, suf[i + 1] - pre[i] - 1);
    }
    cout << ans;
    return 0;
}