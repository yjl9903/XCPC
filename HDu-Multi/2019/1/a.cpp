#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

inline int add(int& x, int y) {
    return (x += y) >= mod ? x -= mod : x;
}
inline int sub(int& x, int y) {
    return (x -= y) < 0 ? x += mod : x;
}
inline int mul(int& x, int y) {
    return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
    int r = 0;
    while (n > 0) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r;
}
inline int inv(int x) {
    return qpow(x, mod - 2);
}

int main() {
    
    return 0;
}