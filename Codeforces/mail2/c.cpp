#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000000 + 5;

ll gcd(ll a, ll b){ return b ? gcd(b, a % b) : a; }

ll la, ra, ta, lb, rb, tb;

ll cal(ll la, ll ra, ll lb, ll rb){
    ll mn = max(la, lb), mx = min(ra, rb);
    return max(0ll, mx - mn + 1);
}

int main(){
    cin >> la >> ra >> ta >> lb >> rb >> tb;
    if (la > lb) swap(la, lb), swap(ra, rb);
    ll g = gcd(ta, tb);
    ll d = (lb - la) / g * g;
    lb -= d; rb -= d;
    ll ans = cal(la, ra, lb, rb);
    ans = max(ans, cal(la, ra, lb - g, rb - g));
    cout << ans;
    return 0;
}