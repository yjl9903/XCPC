#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, k;

ll cal(int a, int b){
    if (b < 0 || b >= k) return 1e18;
    return 1ll * a * k + b;
}

int main(){
    cin >> n >> k;
    ll ans = 1e18;
    for (int i = 1; i * i <= n; i++) {
        if (n % i) continue;
        ans = min(ans, min(cal(i, n / i),cal(n / i, i)));
    }
    cout << ans;
    return 0;
}