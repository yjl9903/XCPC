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
char s[maxn];

namespace sam {
    int sz, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() {
        for (int i = 0; i <= sz; i++) {
            len[i] = link[i] = cnt[i] = 0;
            dep[i] = 0;
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
    int rsort() {
        for (int i = 1; i <= sz; i++) c[i] = 0;
        for (int i = 1; i <= sz; i++) c[len[i]]++;
        for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
        for (int i = 1; i <= sz; i++) a[c[len[i]]--] = i;
        for (int i = sz; i; i--) {
            int u = a[i];
            // cnt[link[p]] += cnt[p];
            dep[link[u]] = min(len[link[u]], max(dep[link[u]], dep[u]));
        }
        int r = inf;
        for (int i = 1; i <= sz; i++) {
            if (dep[i] >= len[link[i]] && dep[i] < len[i]) {
                r = min(r, dep[i] + 1);
            }
        }
        return r;
    }
}
using namespace sam;

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        sam::clear();
        scanf("%d%s", &n, s + 1);
        int slen = strlen(s + 1);
        for (int i = 1; i <= slen; i++) {
            sam::insert(s[i] - 'a');
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
        int mnl = sam::rsort();
        if (mnl == inf) {
            puts("Impossible"); continue;
        }
        string stk, ans;
        function<void(int)> dfs = [&](int u) {
            if (!ans.empty()) return ;
            if ((int)stk.size() >= mnl) return ;
            for (int i = 0; i < 26; i++) {
                if (!ch[u][i]) continue;
                int v = ch[u][i];
                stk += 'a' + i;
                // dbg(stk);
                // dbg(v, dep[v]);
                if (ans.empty() && (int)stk.length() > dep[v]) {
                    assert((int)stk.size() == mnl);
                    ans = stk; break;
                }
                dfs(v);
                stk.pop_back();
            }
        };
        dfs(1);
        if (!ans.empty()) {
            printf("%s\n", ans.c_str());
        } else {
            puts("Impossible");
        }
    }
    return 0;
}