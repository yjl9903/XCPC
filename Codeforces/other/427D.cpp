#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

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
        for (int i = tot; i; i--) {
            int p = a[i];
            cnt[link[p]] += cnt[p];
        }
    }
}
using namespace sam;

char s[maxn];
int vis[maxn];

int main() {
    scanf("%s", s);
    sam::clear();
    for (int i = 0; s[i]; i++) sam::insert(s[i] - 'a');
    sam::rsort();
    scanf("%s", s);
    int u = 1, l = 0;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (ch[u][c]) u = ch[u][c], l++;
        else {
            while (u && !ch[u][c]) u = link[u];
            if (!u) u = 1, l = 0;
            else l = len[u] + 1, u = ch[u][c];
        }
        vis[u]++;
    }
    for (int i = tot; i; i--) vis[link[u]] += vis[u];
    int ans = inf;
    for (int u = 2; u <= tot; u++) {
        if (cnt[u] == 1 && vis[u] == 1) ans = min(ans, len[link[u]] + 1);
    }
    if (ans == inf) puts("-1");
    else cout << ans;
    return 0;
}