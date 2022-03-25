#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n;

int main(){
    cin >> n; int cnt = 0;
    if (n <= 10){ cout << n; return 0; }
    ll a = 9;
    while (a * 10 + 9 < n){
        a = a * 10 + 9;
    }
    ll b = n - a;
    // ll a = n, b;
    // for (; a > 0; a--) if (a % 10 == 9) break;
    // b = n - a;
    while (a){
        cnt += a % 10; a /= 10;
    }
    while (b){
        cnt += b % 10; b /= 10;
    }
    cout << cnt;
    return 0;
}