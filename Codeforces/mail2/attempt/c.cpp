#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int gcd(int a, int b){return b ? gcd(b, a % b) : a;}

int la, ra, ta, lb, rb, tb;

int cal(int la, int lb, int ra, int rb){
    int mn = max(la, lb), mx = min(ra, rb);
    return max(0, mx - mn + 1);
}

int main(){
    cin >> la >> ra >> ta >> lb >> rb >> tb;
    if (ta - 1 == ra) return printf("%d\n", rb - lb + 1), 0;
    if (tb - 1 == rb) return printf("%d\n", ra - la + 1), 0;

    if (la > lb) swap(la, lb), swap(ra, rb), swap(ta, tb);

    int g = gcd(ta, tb), d1 = lb - la;
    if (d1 < g){    
        int ans = cal(la, lb, ra, rb);
        ans = max(ans, cal(la + ta, lb, ra + ta, rb));
        // ans = max(ans, cal(la, lb + tb, ra, rb + tb));
        printf("%d\n", ans);
    }

    return 0;
}