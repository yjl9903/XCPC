#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, m;

int main(){
    cin >> n >> m;    
    if (m == 0) return cout << n << ' ' << n, 0;              
    ll ans1 = m * 2, ans2 = -1;                                                                                                                         
    for (int i = 1; i <= n; i++){                                               
        ll c = 1ll * i * (i - 1) / 2;                                                                                                                   
        if (m >= c){
            ans2 = i;
        }
    }
    if (ans1 >= n) ans1 = 0;
    else ans1 = n - ans1;
    if (ans2 * (ans2 - 1) / 2 == m) ans2 = n - ans2;
    else ans2 = n - ans2 - 1;
    cout << ans1 << ' ' << ans2;
    return 0;
}