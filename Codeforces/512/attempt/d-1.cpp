#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
const int maxn = 1000 + 5;

ll n, m, k, tag;
ll x1, y1, x2, y2;

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
    set<ll> s; map<ll, PLL> mp;
    for (ll i = 1; i <= n; i++){
        for (ll j = 1; j <= m; j++){
            ll t = i * j - tag;
            if (t > 0 && t <= n){
                x2 = i; y1 = j;
                x1 = t; y2 = 1;
                puts("YES");
                printf("0 0\n%I64d %I64d\n%I64d %I64d", x1, y1, x2, y2);
                return 0;
            }
            if (t > 0 && t <= m){
                x2 = i; y1 = j;
                x1 = 1; y2 = t;
                puts("YES");
                printf("0 0\n%I64d %I64d\n%I64d %I64d", x1, y1, x2, y2);
                return 0;
            }
            if (s.count(t)){
                x2 = i; y1 = j;
                x1 = mp[t].first; y2 = mp[t].second;
                puts("YES");
                printf("0 0\n%I64d %I64d\n%I64d %I64d", x1, y1, x2, y2);
                return 0;
            }
            s.insert(i * j); mp[i * j] = make_pair(i, j);
        }
    }
    puts("NO");
    return 0;
}