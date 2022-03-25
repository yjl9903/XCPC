#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, k, s;

int main(){
    scanf("%I64d%I64d%I64d", &n, &k, &s);
    ll ma = k * (n - 1);
    if (s < k || s > ma){
        puts("NO"); return 0;
    }   
    puts("YES");
    ll t = 1;
    for (ll i = k; i > 0; i--){
        ll x = min(n - 1, s - i + 1);
        if (t + x <= n) t += x;
        else t -= x;
        s -= x;
        printf("%I64d ", t);
    }
    return 0;
}