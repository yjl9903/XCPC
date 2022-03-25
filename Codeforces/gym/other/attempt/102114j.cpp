#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <map>
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
const int maxn = 1000000 + 5;

int n, a[maxn];
ll c[maxn], que[maxn << 2];

namespace sam {
    int sz, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        for (int i = 1; i <= sz; i++) {
            len[i] = link[i] = cnt[i] = 0;
            ms(ch[i], 0);
        }
        sz = last = 1;
    }
    int insert(int c) {
        int cur = ++sz, p = last; 
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++sz; 
                len[nq] = len[p] + 1; 
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        return last = cur;
    }
    int c[maxn << 1], a[maxn << 1];
    void rsort() {
        for (int i = 1; i <= sz; i++) c[i] = 0;
        for (int i = 1; i <= sz; i++) c[len[i]]++;
        for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
        for (int i = 1; i <= sz; i++) a[c[len[i]]--] = i;
        for (int i = sz; i; i--) {
            int p = a[i];
            cnt[link[p]] += cnt[p];
        }
    }
}

ll cal() {
    ll ans = 0;
    int ql = 1, qr = 0, pre = 0;
    for (int i = 1; i <= n; i++) {
        if (!c[i]) continue;
        if (pre > 0) {
            int node = i + pre;
            ans += node;
            if (node <= n) c[node]++;
            else que[++qr] = node;
            pre = 0; c[i]--;
        }
        ll cnt = c[i] / 2;
        c[i] -= cnt * 2;
        ans += 2ll * i * cnt;
        if (2 * i <= n) {
            c[2 * i] += cnt;
        } else {
            while (cnt--) {
                que[++qr] = 2 * i;
            }
        }
        if (c[i]) pre = i, c[i]--;
    }
    if (pre > 0 && ql <= qr) {
        ans += pre + que[ql];
        que[++qr] = pre + que[ql];
        ql++; pre = 0;
    }
    while (ql < qr) {
        ll tot = que[ql++];
        tot += que[ql++];
        ans += tot;
        que[++qr] = tot;
    }
    return ans;
}

int main() {
    freopen("../input/1010.in", "r", stdin);
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        sam::clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            sam::insert(a[i]);
        }
        // if (n > 2000) {
        //     puts("");
        //     continue;
        // }
        dbg(n);
        sam::rsort();
        ll fz = cal(), fm = 1ll * n * (n + 1) / 2, g = __gcd(fz, fm);
        if (fm == g) printf("%lld\n", fz / fm);
        else printf("%lld/%lld\n", fz / g, fm / g);
    }
    return 0;
}