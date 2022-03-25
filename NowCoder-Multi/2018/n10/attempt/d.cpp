#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;
const int mod = 998244353;

int get(){
    char ch = getchar(); int x = 0;
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}

ll f[maxn], inv[maxn], finv[maxn];
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1;
    for (int i = 1; i < maxn; i++) f[i] = 1ll * f[i - 1] * i % mod, finv[i] = 1ll * inv[i] * finv[i - 1] % mod;
}
ll C(int n, int m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}

int n, m;

struct ope{
    int k, l, r, x;
    ope(){}
    ope(int kk, int ll, int rr, int xx){
        k = kk; l = ll; r = rr; x = xx;
    }
};
vector<ope> v;
ll cal(int l, int r){
    ll ans = 0;
    int cnt = 0;
    for (int i = v.size() - 1; i >= 0; i--){
        if (v[i].k == 2) cnt++;
        else {
            ll t = 0;
            for (int j = v[i].l; j <= v[i].r; j++){
                if (j > r) break;
                int L = l - j, R = r - j;
                t = (t + C(R + cnt, cnt) - C(L - 1 + cnt, cnt) + mod) % mod;
            }
            ans = (ans + t * 1ll * v[i].x % mod) % mod;
        }
    }
    return ans;
}

int main(){
    init();
    int T; T = get(); 
    // scanf("%d", &T);
    while (T--){
        v.clear();
        // scanf("%d%d", &n, &m);
        n = get(); m = get();
        int cmd, x, y, z;
        while (m--){
            // scanf("%d", &cmd);
            cmd = get();
            if (cmd == 1){
                // scanf("%d%d%d", &x, &y, &z);
                x = get(); y = get(); z = get();
                v.push_back(ope(1, x, y, z));
            }
            else if (cmd == 2){
                v.push_back(ope(2, 0, 0, 0));
            }
            else if (cmd == 3){
                // scanf("%d%d", &x, &y);
                x = get(); y = get();
                printf("%lld\n", cal(x, y));
            }
        }
    }
    return 0;
}