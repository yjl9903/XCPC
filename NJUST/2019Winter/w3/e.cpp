#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, a[maxn];
ll k;

ll get(ll a, ll b) {
    if (a % b == 0) return a / b;
    return a / b + 1;
}

int check(ll d) {
    ll cnt = 0;
    for (int i = 1; i <= n; i++) {
        ll x = get(a[i], d);
        cnt += x * d - a[i];
    }
    // cout << cnt << endl;
    return cnt <= k;
}

int main(){
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; 1ll * j * j <= i; j++) {
            
        }
    }
    return 0;
}