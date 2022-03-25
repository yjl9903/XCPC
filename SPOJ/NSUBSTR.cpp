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
const int maxn = 500000 + 5;

namespace sam {
    int tot, last, len[maxn], cnt[maxn], link[maxn], ch[maxn][26];
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
    void rsort(int ans[]) {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
        for (int i = tot; i; i--) {
            int p = a[i];
            cnt[link[p]] += cnt[p];
        }
        for (int i = tot; i; i--) {
            ans[len[i]] = max(ans[len[i]], cnt[i]);
        }
    }
}

char s[maxn];
int n, ans[maxn];

int main() {
    scanf("%s", s);
    n = strlen(s);
    sam::clear();
    for (int i = 0; i < n; i++) sam::insert(s[i] - 'a');
    sam::rsort(ans);
    for (int i = n - 1; i >= 1; i--) ans[i] = max(ans[i], ans[i + 1]);
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}