#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int fac[maxn], x, y, z, xy, xz, yz, xyz, cnt[8];
int gcd(int a, int b){return b == 0 ? a : gcd(b, a % b);}
ll C(int n, int m){
    ll r = 1;
    for (int i = n - m + 1; i <= n; i++) r *= 1ll * i;
    for (int i = 1; i <= m; i++) r /= 1ll * i;
    return r;
}
bool check(int x, int y, int z){ 
    if ((x & 1) && (y & 2) && (z & 4)) return true;
    if ((y & 1) && (x & 2) && (z & 4)) return true;
    if ((y & 1) && (z & 2) && (x & 4)) return true;
    if ((z & 1) && (y & 2) && (x & 4)) return true;
    if ((z & 1) && (x & 2) && (y & 4)) return true;
    if ((x & 1) && (z & 2) && (y & 4)) return true;
    return false;
}

int main(){
    for (int i = 1; i < maxn; i++) for (int j = i; j < maxn; j += i) fac[j]++;
    int T; cin >> T;
    while (T--){
        cin >> x >> y >> z;
        xy = gcd(x, y); xz = gcd(x, z); yz = gcd(y, z);
        xyz = gcd(xy, z);
        cnt[7] = fac[xyz]; 
        cnt[6] = fac[xy] - fac[xyz];
        cnt[5] = fac[xz] - fac[xyz];
        cnt[4] = fac[x] - fac[xy] - fac[xz] + fac[xyz];
        cnt[3] = fac[yz] - fac[xyz];
        cnt[2] = fac[y] - fac[yz] - fac[xy] + fac[xyz];
        cnt[1] = fac[z] - fac[xz] - fac[yz] + fac[xyz];
        ll ans = 0;
        for (int i = 1; i <= 7; i++) for (int j = i; j <= 7; j++) for (int k = j; k <= 7; k++) if (check(i, j, k)){
            int vis[8] = {0};
            vis[i]++; vis[j]++; vis[k]++;
            ll t = 1;
            for (int i = 1; i <= 7; i++) if (vis[i]) t *= C(cnt[i] + vis[i] - 1, vis[i]);
            ans += t;
        }
        cout << ans << endl;
    }
    return 0;
}