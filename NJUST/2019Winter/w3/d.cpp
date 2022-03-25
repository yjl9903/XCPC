#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 4000 + 5;

ll s[maxn][maxn];

int main(){
    s[0][0] = 1;
    for (int i = 1; i < maxn; i++) s[i][i] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 1; j < i; j++) {
            s[i][j] = (1ll * j * s[i - 1][j] + s[i - 1][j - 1]) % mod;
        }
    }
    int n; cin >> n;
    ll ans = 0;
    for (int i = 1; i <= n; i++) (ans += 1ll * i * s[n][i]) %= mod;
    cout << ans << endl;
    return 0;
}