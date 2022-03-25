#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

ll a, b;

ll cal(ll a) {
    if (a <= 0) return 0;
    ll ans = 0;
    for (int i = 1; i <= 50; i++) {
        ll tot = 1ll << i;
        ll cnt = a / tot * (tot / 2) + max(0ll, a % tot - (tot / 2) + 1);
        if (cnt % 2ll == 1ll) ans ^= 1ll << (i - 1);
    }
    return ans;
}

int main() {
    cin >> a >> b;
    // cal(a - 1);
    // cal(b);
    cout << (cal(a - 1) ^ cal(b)) << endl;
    return 0;
}