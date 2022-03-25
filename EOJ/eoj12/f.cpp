#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const int maxn = 600000 + 5;

namespace sam {
    int tot, last, len[maxn], cnt[maxn], link[maxn], ch[maxn][26];
    ll res;
    void clear() { 
        res = 0;
        ms(ch, 0); ms(cnt, 0); tot = last = 1; 
    }
    ll insert(int c) {
        int cur = ++tot, p = last;
        len[cur] = len[last] + 1; cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; len[nq] = len[p] + 1;
                link[nq] = link[q]; link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        } 
        last = cur;
        return res = res + len[cur] - len[link[cur]];
    }
    int c[maxn], a[maxn];
    void rsort() {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
    }
}

char s[maxn];
int n, q;
ll ans[maxn];

int main() {
    sam::clear();
    scanf("%d%d%s", &n, &q, s + 1);
    for (int i = 1; i <= n; i++) ans[i] = sam::insert(s[i] - 'a');
    for (int i = 1; i <= n; i++) ans[i + n] = sam::insert(s[i] - 'a');
    for (int i = 1; i <= n; i++) ans[i + n + n] = sam::insert(s[i] - 'a');
    ll dt = ans[3 * n] - ans[3 * n - 1];
    for (int i = 2 * n + 1; i <= 3 * n; i++) {
        dbg(i, ans[i]);
    }
    while (q--) {
        int x; scanf("%d", &x);
        if (x <= 2 * n) printf("%lld\n", ans[x]);
        else printf("%lld\n", ans[2 * n] + dt * (x - 2 * n));
    }
    return 0;
}