#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;
const int maxl = 62;

int n, m;
ll a[maxl + 5], k[maxn];
vector<ll> v;
bool insert(ll x){
    for (int j = maxl; j >= 0; j--){
        if (x & (1ll << j)){
            if (a[j]) x ^= a[j];
            else {
                for (int k = 0; k < j; k++) if (x & (1ll << k)) x ^= a[k];
                for (int k = j + 1; k <= maxl; k++) if (a[k] & (1ll << j)) a[k] ^= x;
                a[j] = x;
                return true;
            }
        }
    }
    return false;
}
void build(){
    ms(a, 0); v.clear();
    for (int i = 0; i < n; i++) insert(k[i]);
    for (int i = 0; i < maxl; i++) if (a[i]) v.push_back(a[i]);
}
ll query(ll k){
    if (v.size() != n) k--;
    if (k >= (1ll << v.size())) return -1;
    ll ans = 0;
    for (int i = 0; i < v.size(); i++) if (k & (1ll << i)){
        ans ^= v[i];
    }
    return ans;
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%lld", &k[i]);
        build();
        scanf("%d", &m);
        printf("Case #%d:\n", ++kase);
        while (m--){
            ll x; scanf("%lld", &x);
            printf("%lld\n", query(x));
        }
    }
    return 0;
}