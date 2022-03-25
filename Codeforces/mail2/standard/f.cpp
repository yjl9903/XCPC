#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int n, l[maxn], r[maxn], from[maxn], to[maxn];
ll k, w[maxn];

int main(){
    scanf("%d%I64d", &n, &k);
    for (int i = 2; i <= n; i++){
        int f; ll x; scanf("%d%I64d", &f, &x);
        w[i] = w[f] ^ x;
    }
    for (int i = 0; i <= n; i++) from[i] = 1, to[i] = n;
    sort(w + 1, w + n + 1);
    ll ans = 0;
    for (int b = 61; b >= 0; b--){
        int beg = 1;
        while (beg <= n){
            int last = beg;
            while (last + 1 <= n && (w[last] ^ w[last + 1]) < (1ll << b)) last++;
            r[beg] = last; l[last] = beg; beg = last + 1;
        }
        // split w[n] : i...r[i] / l[i]...i -> w[x] ^ w[i] < 0001000 -> the b-th digit of w[x] ^ w[i] is 0
        ll sum = 0, flag = 0;
        for (int i = 1; i <= n; i++){
            if (from[i] > to[i]) continue;
            if (w[i] & (1ll << b)){
                if (w[to[i]] & (1ll << b)){
                    sum += to[i] - l[to[i]] + 1;
                }
            }
            else {
                if ((w[from[i]] & (1ll << b)) == 0){
                    sum += r[from[i]] - from[i] + 1;
                }
            }
        }
        if (sum < k){
            k -= sum; ans += 1ll << b; flag = 1;
        }
        // what's the meaning of from[n] and to[n] ?
        // from[n] and to[n] -> the range of i-th node in trie
        for (int i = 1; i <= n; i++){
            if (from[i] > to[i]) continue;
            // e.g. tot digit of ans = 1, so flag = 1
            // then if the b-th digit of w[i] = 1
            // the b-th digit of left border = 1
            // so this node cannot be counted afterwards
            // maintain from[i] and to[i] seems to subtree[i]'s in[i] and out[i] ?
            if (((w[i] >> b) & 1) == flag){
                if (w[from[i]] & (1ll << b)) to[i] = -1;
                else to[i] = r[from[i]];
            }
            else {
                if (w[to[i]] & (1ll << b)) from[i] = l[to[i]];
                else from[i] = n + 1;
            }
        }
    }
    printf("%I64d", ans);
    return 0;
}