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

int n;

int main(){
    cin >> n;
    ll x = 1, y = 0;
    for (ll i = n; i > 1; i--) x = x * i % mod, y = (x + y) % mod;
    // cout << x << ' ' << y << endl;
    cout << (n * x % mod - y + mod) % mod;
    return 0;
}