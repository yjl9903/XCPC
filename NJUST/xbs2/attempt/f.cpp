#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1000000007;
const int maxn = 1000000 + 5;

char s[maxn], t[maxn];

namespace sam{
    int len[maxn], cnt[maxn], link[maxn], tot, last;
    map<int,int> ch[maxn];
    void init(){ 
        // ms(ch, 0); 
        for (int i = 1; i <= tot; i++) ch[i].clear();
        ms(cnt, 0); tot = last = 1; 
    }
    void insert(int c){
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
                // memcpy(ch[nq], ch[q], sizeof ch[q]);
                ch[nq] = ch[q];
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        } 
        last = cur;
    }
    int c[maxn], a[maxn];
    void rsort(){
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
        for (int i = tot; i; i--){
            int p = a[i];
            cnt[link[p]] += cnt[p];
        }
    }
    ll cal(char* t) {
        ll ans = 0;
        int now = 1;
        for (int i = 0; t[i]; i++) {
            now = ch[now][t[i] - 'a'];
            ans += 1ll * cnt[now] * (i + 1) % mod;
            if (ans >= mod) ans -= mod;
        }
        return ans;
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s%s", s, t);
        int n = strlen(s), m = strlen(t);
        reverse(s, s + n); reverse(t, t + m);
        sam::init();
        for (int i = 0; i < n; i++) sam::insert(s[i] - 'a');
        sam::rsort();
        printf("%lld\n", sam::cal(t));
    }
    return 0;
}