#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <functional>
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
const int maxn = 250000 + 5;

int n, dep[maxn << 2];
char s[maxn], t[maxn];

namespace SA {
    int n, m, sa[maxn], h[maxn], c[maxn], x[maxn], y[maxn];
    void rsort() {
        for (int i = 1; i <= m; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) c[x[i]]++;
        for (int i = 1; i <= m; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
    }
    int cmp(int i, int j, int k) {
        int a = i + k > n ? -1 : y[i + k];
        int b = j + k > n ? -1 : y[j + k];
        return y[i] == y[j] && a == b;
    }
    void build(int nn, char* s) {
        n = nn; m = 255; // important
        for (int i = 1; i <= n; i++) x[i] = s[i], y[i] = i;
        rsort();
        for (int k = 1, p; k <= n; k += k, m = p) {
            p = 0;
            for (int i = n; i > n - k; i--) y[++p] = i;
            for (int i = 1; i <= n; i++) if (sa[i] > k) y[++p] = sa[i] - k;
            rsort();
            for (int i = 1; i <= n; i++) swap(x[i], y[i]);
            x[sa[1]] = p = 1;
            for (int i = 2; i <= n; i++) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p : ++p;
        }
        for (int i = 1; i <= n; i++) x[sa[i]] = i;
        for (int i = 1, k = 0; i <= n; i++) {
            if (k) k--;
            int j = sa[x[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
            h[x[i]] = k;
        }
    }
}

namespace sam {
    int sz, last, cnt[maxn << 1], pos[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() {
        for (int i = 0; i <= sz; i++) {
            len[i] = link[i] = cnt[i] = 0;
            dep[i] = 0;
            ms(ch[i], 0);
        }
        sz = last = 1;
    }
    int insert(int c, int i) {
        int cur = ++sz, p = last;
        len[cur] = len[last] + 1;
        cnt[cur] = 1;
        pos[cur] = i;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++sz;
                len[nq] = len[p] + 1;
                pos[nq] = pos[q];
                link[nq] = link[q];
                link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        return last = cur;
    }
    int c[maxn << 1], a[maxn << 1];
    string solve() {
        for (int i = 1; i <= sz; i++) c[i] = 0;
        for (int i = 1; i <= sz; i++) c[len[i]]++;
        for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
        for (int i = 1; i <= sz; i++) a[c[len[i]]--] = i;
        for (int i = sz; i; i--) {
            int u = a[i];
            dep[link[u]] = min(len[link[u]], max(dep[link[u]], dep[u]));
        }
        int r = inf; vector<int> v;
        for (int i = 1; i <= sz; i++) {
            if (dep[i] >= len[i]) continue;
            int t = max(len[link[i]], dep[i]) + 1;
            if (t < r) {
                r = t; v.clear(); v.push_back(pos[i] - r + 1);
            } else if (t == r) {
                v.push_back(pos[i] - r + 1);
            }
        }
        if (r == inf) return "Impossible";
        else {
            int st = v[0];
            for (int p: v) {
                // dbg(st, p, SA::x[st], SA::x[p]);
                if (SA::x[st] > SA::x[p]) {
                    st = p;
                }
            }
            string ans;
            // dbg(st, r);
            for (int i = st; i <= st + r - 1; i++) ans += t[i];
            return ans;
        }
    }
}
using namespace sam;

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        sam::clear();
        scanf("%d%s", &n, s + 1);
        int slen = strlen(s + 1);
        SA::build(slen, s);
        for (int i = 1; i <= slen; i++) {
            t[i] = s[i];
            sam::insert(s[i] - 'a', i);
        }
        for (int i = 2; i <= n; i++) {
            scanf("%s", s + 1);
            int u = 1, l = 0;
            for (int i = 1; s[i]; i++) {
                int c = s[i] - 'a';
                if (ch[u][c]) u = ch[u][c], l++;
                else {
                    while (u && !ch[u][c]) u = link[u];
                    if (!u) u = 1, l = 0;
                    else l = len[u] + 1, u = ch[u][c];
                }
                dep[u] = min(len[u], max(dep[u], l));
            }
        }
        printf("Case #%d: ", ++kase);
        printf("%s\n", sam::solve().c_str());
    }
    return 0;
}