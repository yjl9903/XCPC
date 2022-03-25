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
const int maxn = 400000 + 5;

int p, q;
char s[maxn];

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
    ll f[maxn];
    ll get(int n, char* s) {
        f[1] = p;
        insert(s[1] - 'a');
        int l = 2, r = 1, cur = 1;
        auto back = [&](int l) {
            while (cur && len[link[cur]] >= l) cur = link[cur];
            if (cur == 0) cur = 1;
        };
        for (int i = 2; i <= n; i++) {
            f[i] = f[i - 1] + p; r++;
            int c = s[i] - 'a';
            while (!ch[cur][c] && l <= r) {
                insert(s[l++] - 'a');
                back(r - l);
            }
            cur = ch[cur][c];
            back(r - l + 1);
            if (l <= r) f[i] = min(f[i], f[i - (r - l + 1)] + q);
        }
        return f[n];
    }
}

int main() {
    while (scanf("%s%d%d", s + 1, &p, &q) == 3) {
        sam::clear();
        printf("%lld\n", sam::get(strlen(s + 1), s));
    }
    return 0;
}