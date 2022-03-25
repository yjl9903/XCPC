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
    int len[maxn], cnt[maxn], link[maxn], ch[maxn][26], tot, last;
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
    }
}
using namespace sam;

char s[maxn];
int dep[maxn], ans[maxn];

int main() {
    sam::clear();
    scanf("%s", s + 1);
    for (int i = 1; s[i]; i++) sam::insert(s[i] - 'a');
    sam::rsort();
    for (int i = 1; i <= tot; i++) ans[i] = len[i];
    while (scanf("%s", s + 1) == 1) {
        ms(dep, 0);
        int u = 1, l = 0;
        for (int i = 1; s[i]; i++) {
            int c = s[i] - 'a';
            if (ch[u][c]) u = ch[u][c], l++;
            else {
                while (u && !ch[u][c]) u = link[u];
                if (!u) u = 1, l = 0;
                else l = len[u] + 1, u = ch[u][c];
            }
            dep[u] = max(dep[u], l);
        }
        for (int i = tot; i >= 1; i--) {
            int u = sam::a[i];
            dep[link[u]] = max(dep[u], dep[link[u]]);
        }
        for (int i = tot; i >= 1; i--) ans[i] = min(ans[i], dep[i]);
    }
    int res = 0;
    for (int i = 1; i <= tot; i++) res = max(res, ans[i]);
    printf("%d", res);
    return 0;
}