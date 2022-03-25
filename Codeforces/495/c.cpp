#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn], vis[maxn];

int main(){
    cin >> n; ms(vis, 0);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) vis[a[i]]++;

    ll ans = 0;
    for (int i = 1; i <= maxn; i++) if (vis[i] > 1) ans++;

    map<int, int> mp; mp.clear();
    for (int i = n - 1; i >= 0; i--){
        if (mp.count(a[i])){
            ans += ll(mp.size() - 1 - mp[a[i]]);
            mp[a[i]] = mp.size() - 1;
        }
        else{
            int t = mp.size();
            ans += ll(t);
            mp[a[i]] = t;
        }
    }    

    cout << ans;
    return 0;
}