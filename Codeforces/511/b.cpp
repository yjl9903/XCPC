#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;

int main(){
    cin >> n;
    ll ans = 0;
    for (int i = 0, x, y; i < n; i++){
        cin >> x >> y;
        ans = max(1ll * x + 1ll * y, ans);
    }
    cout << ans;
    return 0;
}