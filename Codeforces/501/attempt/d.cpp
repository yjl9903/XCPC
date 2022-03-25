#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, k, s;

int main(){
    scanf("%I64d%I64d%I64d", &n, &k, &s);
    ll ma = k * (n - 1);
    if (s < k || s > ma){
        puts("NO"); return 0;
    }   
    puts("YES");
    ll l = s / k, t = 1;
    if (s % k) l++;
    for (int i = 0; i < k - 1; i++){
        s -= l;
        if (t + l <= n) t += l;
        else {
            t -= l;
        }
        printf("%I64d ", t);
        ll c = s / (k - i - 1);
        if (s & c) c++;
        if (t - c > 0 || t + c <= n) l = c;
    }
    if (t + s <= n) t += s;
    else t -= s;
    printf("%I64d", t);
    return 0;
}