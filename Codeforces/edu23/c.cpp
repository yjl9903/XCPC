#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, s;

int check(ll x){
    ll a = x, sum = 0;
    while (a){
        sum += a % 10; a /= 10;
    }
    return x - sum >= s;
}

int main(){
    cin >> n >> s;
    ll l = 1, r = n, ans = n + 1;
    while (l <= r){
        ll m = (l + r) / 2;
        if (check(m)) ans = m, r = m - 1;
        else l = m + 1;
    }
    cout << n - ans + 1 << endl;
    return 0;
}