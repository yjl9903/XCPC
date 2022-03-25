#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, k;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%lld%lld", &n, &k);
        if (n == 1){
            puts("1 1"); continue;
        }
        ll sq = (ll)sqrt(1.0 * n);
        // if (sq * (sq + 1) > n) sq--;
        ll c = n / (sq + 1);
        dbg(sq, c);
        if (k <= sq){
            printf("%lld %lld\n", sq + c, n / k);
        }
        else {
            dbg(c - k + sq);
            ll ans = n / (c - k + sq + 1);
            printf("%lld %lld\n", sq + c, ans);
        }
        for (ll i = n; i > 0; i--){
            printf("%lld\n", n / i);
        }
    }
    return 0;
}