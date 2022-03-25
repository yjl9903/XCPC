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
const int mod = 2012;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

namespace sam {
    int tot, last, len[maxn], link[maxn], ch[maxn][11];
    void clear() { 
        ms(ch, 0); tot = last = 1; 
    }
    void insert(int c) {
        int cur = ++tot, p = last;
        len[cur] = len[last] + 1;
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
    int cnt[maxn], val[maxn];
    int get() {
        for (int i = 0; i <= tot; i++) cnt[i] = val[i] = 0;
        rsort(); cnt[1] = 1;
        int ans = 0;
        for (int i = 1; i <= tot; i++) {
            int u = a[i];
            ans = (ans + val[u]) % mod;
            for (int c = 0; c < 10; c++) {
                int v = ch[u][c];
                if (!v) continue;
                if (u == 1 && c == 0) continue;
                cnt[v] += cnt[u];
                val[v] += (10ll * val[u] + 1ll * c * cnt[u]) % mod;
                if (val[v] >= mod) val[v] -= mod;
            }
        }
        return ans;
    }
}
using namespace sam;

int n;
char s[maxn];

int main() {
    while (scanf("%d", &n) == 1) {
        sam::clear();
        for (int i = 1; i <= n; i++) {
            scanf("%s", s);
            sam::last = 1;
            for (int j = 0; s[j]; j++) sam::insert(s[j] - '0');
        }
        printf("%d\n", sam::get());
    }
    return 0;
}