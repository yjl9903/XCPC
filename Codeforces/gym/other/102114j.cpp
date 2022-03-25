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
    int tot, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1];
    // unordered_map<int,int> ch[maxn << 1];
    vector<PII> ch[maxn << 1];
    void clear() {
        for (int i = 1; i <= tot; i++) {
            cnt[i] = len[i] = link[i] = 0;
            ch[i].clear(); 
        }
        tot = last = 1;
    }
    int getch(int u, int c) {
        for (auto& x: ch[u]) {
            if (x.first == c) return x.second;
        }
        return -1;
    }
    int insert(int c) {
        int cur = ++tot, p = last; 
        ch[cur].clear();
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        for (; p && getch(p, c) == -1; p = link[p]) ch[p].push_back({c, cur});
        if (!p) link[cur] = 1;
        else {
            int q = getch(p, c);
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; 
                len[nq] = len[p] + 1; 
                cnt[nq] = 0;
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                ch[nq] = vector<PII>(ch[q]);
                for (int flag = 1; flag; p = link[p]) {
                    flag = 0;
                    for (auto& x: ch[p]) {
                        if (x.first == c && x.second == q) {
                            x.second = nq;
                            flag = 1;
                            break;
                        }
                    }
                }
            }
        }
        return last = cur;
    }
    int c[maxn << 1], a[maxn << 1];
    void rsort() {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
        for (int i = tot; i; i--) {
            int p = a[i];
            cnt[link[p]] += cnt[p];
        }
        for (int i = 1; i <= tot; i++) {
            ::c[cnt[i]] += len[i] - len[link[i]];
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
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        sam::clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            sam::insert(a[i]);
        }
        sam::rsort();
        ll fz = cal(), fm = 1ll * n * (n + 1) / 2, g = __gcd(fz, fm);
        if (fm == g) printf("%lld\n", fz / fm);
        else printf("%lld/%lld\n", fz / g, fm / g);
    }
    return 0;
}