#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

namespace sam {
    int ch[maxn][26], link[maxn], len[maxn], cnt[maxn], last, sz;
    void clear() {
        sz = last = 1;
    }
    void insert(int c) {
        int cur = ++sz, p = last; 
        len[cur] = len[last] + 1; cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++sz; len[nq] = len[p] + 1;
                link[nq] = link[q]; link[cur] = link[q] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        last = cur;
    }
    int c[maxn], a[maxn], sum[maxn];
    void rsort(int t) {
        for (int i = 1; i <= sz; i++) c[len[i]]++;
        for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
        for (int i = 1; i <= sz; i++) a[c[len[i]]--] = i;
        for (int i = sz; i >= 1; i--) {
            int p = a[i];
            if (t) cnt[link[p]] += cnt[p];
            else cnt[p] = 1;
        }
        cnt[1] = 0;
        for (int i = sz; i >= 1; i--) {
            int p = a[i];
            sum[p] = cnt[p];
            for (int j = 0; j < 26; j++) {
                if (ch[p][j])
                    sum[p] += sum[ch[p][j]];
            }
        }
    }
    string query(int k) {
        if (k > sum[1]) return string("-1");
        int u = 1; string ans; k -= cnt[1];
        while (k > 0) {
            int c = 0;
            while (k > sum[ch[u][c]]) {
                k -= sum[ch[u][c]]; c++;
            }
            u = ch[u][c]; ans += ('a' + c); k -= cnt[u];
        }
        return ans;
    }
}

int n, k, t; char s[maxn];

int main() {
    sam::clear();
    scanf("%s%d%d", s, &t, &k);
    for (int i = 0; s[i]; i++) sam::insert(s[i] - 'a');
    sam::rsort(t);
    printf("%s", sam::query(k).c_str());
    return 0;
}