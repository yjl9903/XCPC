#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, m, k;
ll gcd(ll a, ll b){return b ? gcd(b, a % b) : a;}

int main(){
    cin >> n >> m >> k;
    if (2 * n * m % k) return puts("NO"), 0;
    puts("YES");
    puts("0 0");
    if (k % 2 == 0){
        k /= 2;
        ll g = gcd(n, k);
        printf("%I64d 0\n0 %I64d", n / g, m / (k / g));
    }
    else {
        ll g = gcd(n, k), a = n / g, b = m / (k / g);
        if (g == 1) b *= 2;
        else a *= 2;
        printf("%I64d 0\n0 %I64d", a, b);
    }
    return 0;
}

/*
ab = 2nm/k
-> 2nm % k == 0

g = gcd(n, k)
a = n / gcd
b = m / (k / gcd)

*/