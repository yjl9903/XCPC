#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int w, h, k;

int main(){
    cin >> w >> h >> k;
    ll ans = 0;
    for (int i = 1; i <= k; i++){
        ans += (w - 4 * (i - 1) + h - 4 * (i - 1) - 2) * 2;
    }
    cout << ans;
    return 0;
}