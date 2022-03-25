#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll gcd(ll a, ll b){return b ? gcd(b, a % b) : a;}
ll x3, y3, x2, y2;

ll k = 1;
ll cal(ll a, ll b){
    map<ll,int> mp;
    for (ll i = 2; i * i <= a; i++){
        if (a % i) continue;
        int c = 0; while (a % i == 0) c++, a /= i;
        mp[i] = c;
    }
    if (a > 1) mp[a]++;
    for (ll i = 2; i * i <= b; i++){
        if (b % i) continue;
        int c = 0; while (b % i == 0) c++, b /= i;
        if (mp[i] < c) {
            if (mp[i] == 0) continue;
            int s = c - mp[i];
            while (s--) k *= i;
            mp[i] = 0;
        }
        else mp[i] -= c;
    }
    if (b > 1){
        if (mp[b] == 0) k *= b;
        else mp[b]--;
    } 
    ll r = 1;
    for (auto& x : mp){
        if (x.second == 0) continue;
        int c = x.second;
        while (c--) r *= x.first;
    }
    k = (k - 1) / 2;
    return (r - 1) / 2;
}
double dis(double x, double y){
    x -= (double)x3; y -= (double)y3;
    return sqrt(x * x + y * y);
}

int main(){
    cin >> x3 >> y3 >> x2 >> y2;
    if (x3 == x2){
        ll d = abs(y3 - y2);
        if (d % 2) puts("NO");
        else cout << x3 << ' ' << min(y3, y2) + d / 2 << endl;
        return 0;
    }
    if (y3 == y2){
        ll d = abs(x3 - x2);
        if (d % 2) puts("NO");
        else cout << min(x3, x2) + d / 2 << ' ' << y3 << endl;
        return 0;
    }
    ll mx = (x3 + x2) / 2, my = (y3 + y2) / 2;
    if (x3 + x2 == 2ll * mx && y3 + y2 == 2ll * my){
        cout << mx << ' ' << my << endl; return 0;
    }
    if (x3 + x2 == 2ll * mx || y3 + y2 == 2ll * my) return puts("NO"), 0;
    
    if (x3 > x2) swap(x3, x2), swap(y3, y2);
    ll dx = x2 - x3, dy = y2 - y3;
    int flag = 1; if (dy < 0) dy = -dy, flag = 0;
    ll g = gcd(dx, dy); dx /= g; dy /= g;

    ll m = cal(dy, dx);
    ll ansx = mx - m, ansy = my + flag + k;
    if (dis(1.0 * ansx, 1.0 * ansy) > dis(1.0 * x2, 1.0 * y2)) puts("NO");
    else cout << ansx << ' ' << ansy << endl;

    return 0;
}