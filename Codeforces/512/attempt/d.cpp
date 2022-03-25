#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, m, k, tag;
ll x1, y1, x2, y2;

bool check2(){
    ll t = abs(tag - x2 * y1);
    for (ll i = 1; i <= n; i++){
        if (t % i == 0){

            exit(0);
        }
    }
}
bool check1(){
    ll l = 1, r = m;
    while (l <= r){
        ll m = (l + r) >> 1;
        y1 = m;
        if (check2()){

        }
        else {

        }
    }
}

int main(){
    cin >> n >> m >> k;
    if (k > 2 * n * m || 2 * n * m % k){
        puts("NO"); return 0;
    }
    if (k == 2 * n * m){
        printf("YES\n0 0\n0 1\n1 0\n"); 
        return 0;
    }
    if (k == 2){
        printf("YES\n0 0\n0 %I64d\n%I64d 0\n", n, m);
        return 0;
    }
    tag = 2 * n * m / k;

    return 0;
}