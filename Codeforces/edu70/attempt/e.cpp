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
const int maxn = 200000 + 5;

char s[maxn], t[maxn];
int n, slen, vis[maxn];
string str[maxn];

namespace sam {
    int tot, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        tot = last = 1; ms(ch[1], 0);
    }
    void insert(int c) {
        int cur = ++tot, p = last; 
        ms(ch[cur], 0);
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; 
                len[nq] = len[p] + 1; 
                cnt[nq] = 0;
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        last = cur;
    }
    int c[maxn << 1], a[maxn << 1];
    void rsort() {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
    }
}
using namespace sam;

int main() {
    sam::clear();
    scanf("%s%d", s + 1, &n);
    slen = strlen(s + 1);
    for (int i = 1; i <= slen; i++) sam::insert(s[i] - 'a');
    sam::rsort();
    for (int i = 1; i <= n; i++) {
        scanf("%s", t + 1);
        str[i] = string(t + 1);
        int tlen = strlen(t + 1), u = 1, l = 0;
        for (int i = 1; i <= tlen; i++) {
            int c = t[i] - 'a';
            if (ch[u][c]) u = ch[u][c], l++;
            else {
                while (u && !ch[u][c]) u = link[u];
                if (!u) u = 1, l = 0;
                else l = len[u] + 1, u = ch[u][c];
            }
            if (l == tlen) {
                vis[u]++;
            }
        }
    }
    
    return 0;
}