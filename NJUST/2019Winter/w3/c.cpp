#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

bool isp(ll n) {
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int n;

int main(){
    cin >> n;
    if (n == 2) return puts("1"), 0;
    if (n % 2 == 0) return puts("2"), 0;
    if (isp(n)) return puts("1"), 0;
    if (isp(n - 2)) return puts("2"), 0;
    puts("3");
    return 0;
}