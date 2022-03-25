#include <iostream>
#include <cstdio>
#include <cstring>
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
const int maxn = 300000 + 5;

int n, a[maxn], suf[maxn], s[maxn][2];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        ll x; scanf("%I64d", &x); int &t = a[i];
        while (x){
            if (x & 1) t++;
            x >>= 1;
        }
    }
    s[n][0] = 1;
    ll ans = 0; int suf = 0;
    for (int i = n - 1; i >= 0; i--){
        int sum = 0, mx = 0;
        for (int j = i; j < n && j - i < 63; j++){
            sum += a[j]; mx = max(mx, a[j]);
            if (mx > sum - mx && sum % 2 == 0) ans--;
        }

        suf += a[i];
        ans += 1ll * s[i + 1][suf & 1];
        s[i][0] = s[i + 1][0]; s[i][1] = s[i + 1][1];
        s[i][suf & 1]++;
    }
    printf("%I64d", ans);
    return 0;
}