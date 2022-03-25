#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int n, tot, a[maxn], b[maxn], ch[maxn][2], siz[maxn];
ll k, w[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%I64d", &n, &k);
        ms(a, 0); ms(b, 0); ms(ch, 0); ms(siz, 0); ms(w, 0);
        for (int i = 1; i <= n; i++) w[i] = 0;
        for (int i = 2; i <= n; i++) {
            int f; ll x; scanf("%d%I64d", &f, &x);
            w[i] = w[f] ^ x;
        }
        for (int i = 1; i <= n; i++) a[i] = b[i] = 1;
        ll ans = 0; tot = n;
        for (int t = 62; t >= 0; t--) {
            for (int i = 1; i <= tot; i++) ch[i][0] = ch[i][1] = siz[i] = 0;
            tot = 0; ll s = 0, flag = 0;
            for (int i = 1; i <= n; i++) {
                int b = w[i] >> t & 1;
                if (ch[a[i]][b]) a[i] = ch[a[i]][b];
                else a[i] = ch[a[i]][b] = ++tot;
                siz[a[i]]++;
            }
            for (int i = 1; i <= n; i++) {
                s += siz[ch[b[i]][w[i] >> t & 1]];
            }
            if (s < k) k -= s, flag = 1, ans += 1ll << t;
            for (int i = 1; i <= n; i++) {
                b[i] = ch[b[i]][(w[i] >> t & 1) ^ flag];
            }
        }
        printf("%I64d\n", ans);
    }   
    return 0;
}