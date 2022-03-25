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
const int maxn = 200000 + 5;

namespace sam {
    int tot, last, len[maxn], cnt[maxn], link[maxn], ch[maxn][60];
    void clear() { 
        ms(ch, 0); ms(cnt, 0); tot = last = 1; 
    }
    void insert(int c) {
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
    }
    int c[maxn], a[maxn];
    void rsort() {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
        for (int i = tot; i; i--) {
            int p = a[i];
            cnt[link[p]] += cnt[p];
        }
    }
}
using namespace sam;

char s[maxn];
int n, m, k, vis[maxn];

int f(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    else return c - 'A' + 27;   
}

int main() {
    while (scanf("%d", &k) == 1 && k) {
        scanf("%s", s + 1);
        sam::clear();
        ms(vis, 0);
        for (int i = 1; s[i]; i++) sam::insert(f(s[i]));
        sam::rsort();
        scanf("%s", s + 1);
        ll ans = 0;
        int u = 1, l = 0;
        for (int i = 1; s[i]; i++) {
            int c = f(s[i]);
            if (ch[u][c]) u = ch[u][c], l++;
            else {
                while (u && !ch[u][c]) u = link[u];
                if (!u) u = 1, l = 0;
                else l = len[u] + 1, u = ch[u][c];
            }
            if (l >= k) {
                ans += 1ll * cnt[u] * (l - max(k, len[link[u]] + 1) + 1);
                if (len[link[u]] >= k) vis[link[u]]++;
            }
        }
        for (int i = tot; i >= 1; i--) {
            int u = a[i];
            ans += 1ll * vis[u] * (len[u] - max(k, len[link[u]] + 1) + 1) * cnt[u];
            if (len[link[u]] >= k) vis[link[u]] += vis[u];
        }
        printf("%lld\n", ans);
    }
    return 0;
}