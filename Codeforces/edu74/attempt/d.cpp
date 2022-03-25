#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const int maxn = 300000 + 5;

namespace pam {
    int sz, tot, last;
    int ch[maxn][26], len[maxn], fail[maxn];
    int cnt[maxn], dep[maxn];
    char s[maxn];
    int node(int l) {
        sz++; ms(ch[sz], 0);
        len[sz] = l; fail[sz] = cnt[sz] = dep[sz] = 0;
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
    int insert(char c) {
        s[++tot] = c;
        int now = getfail(last);
        if (!ch[now][c - 'a']) {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail(fail[now])][c - 'a'];
            dep[x] = dep[fail[x]] + 1;
            ch[now][c - 'a'] = x;
        }
        last = ch[now][c - 'a'];
        cnt[last]++;
        return last;
    }
    void count() {
        for (int i = sz; i >= 0; i--) {
            cnt[fail[i]] += cnt[i];
        }
    }
}
using namespace pam;

char ss[maxn];
int n, pos[maxn];

int a[maxn];
int get(int u) {
    if (len[u] <= 1) return inf;
    if (a[u] != -1) return a[u];
    return a[u] = min(len[u], get(fail[u]));
}

int main() {
    pam::clear();
    scanf("%d%s", &n, ss + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = -1;
        pos[i] = pam::insert(ss[i]);
    }
    ll ans = 0;
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int mn = r - get(pos[r]) + 1;
            if (mn >= r) {
                ans += n - r + 1;
                dbg(l, r);
                break;
            }
        }
    }
    cout << ans;
    // for (int i = 1; i <= n; i++) {
    //     int u = pam::insert(s[i]);
    //     if (pam::len[u] > 1) {
    //         int l = i - pam::len[u] + 1, r = i;
    //         ans[l]++; ans[r + 1]--;
    //     }
    // }
    // for (int i = 1; i <= n; i++) ans[i] += ans[i - 1];
    // ll res = 0; int last = 0;
    // for (int i = 1; i <= n; i++) {
    //     dbg(ans[i]);
    // }
    // for (int i = 1; i <= n + 1; i++) {
    //     if (i == n + 1 || ans[i] == 0) {
    //         int l = i - last - 1;
    //         res += 1ll * l * (l + 1) / 2;
    //         last = i;
    //     }
    // }
    // cout << res;
    return 0;
}