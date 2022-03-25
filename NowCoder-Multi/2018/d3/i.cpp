#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const ll mod = 998244353;

int n;

int main(){
    scanf("%d", &n);
    ll ans1 = 1, ans2 = 0;
    for (int i = 0; i < n; i++){
        ll x; scanf("%lld", &x);
        ans1 = (ans1 * (x + 1)) % mod;
        ans2 = (ans2 + x * (x + 1) / 2) % mod;
    }
    printf("%lld\n", (ans1 + ans2) % mod);
    return 0;
}