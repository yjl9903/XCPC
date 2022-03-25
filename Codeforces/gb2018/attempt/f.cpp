#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, cw[maxn];
ll l[maxn], suf[maxn];
char s[maxn];
vector<ll> a, a2;
vector<char> tp, tp2;

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%I64d", l + i);
    scanf("%s", s);
    a.push_back(l[0]); tp.push_back(s[0]);
    for (int i = 1; i < n; i++) {
        if (tp.back() == s[i]) {
            ll x = a.back(); a.pop_back();
            a.push_back(x + l[i]);
        } else a.push_back(l[i]), tp.push_back(s[i]);
    }
    cw[0] = (tp[0] == 'W');
    for (int i = 1; i < tp.size(); i++) cw[i] = cw[i - 1] + (tp[i] == 'W');

    ll ans = 0;
    // for (int i = 0; i < a.size(); i++) {
    //     // cout << a[i] << ' ' << tp[i] << endl;
    //     if (tp[i] == 'W') {
    //         a2.push_back(a[i]), tp2.push_back('W');
    //         // ans += a[i] / 2ll * 4ll;
    //         // if (a[i] % 2) a2.push_back(1), tp2.push_back('W');
    //     } else if (tp[i] == 'G') {
    //         a2.push_back(a[i]), tp2.push_back('G');
    //         // ans += a[i] / 2ll * 6ll;
    //         // if (a[i] % 2) a2.push_back(1), tp2.push_back('G');
    //     } else {
    //         int c = 6;
    //         if (cw[i]) c = 4;
    //         ans += a[i] * c;
    //     }
    // } 
    // a = a2; tp = tp2;

    for (int i = a.size(); i >= 0; i--) {
        suf[i] = suf[i + 1];
        if (tp[i] == 'G') suf[i] += a[i];
    }

    ll e = 0;
    for (int i = 0; i < a.size(); i++) {
        if (tp[i] == 'G') {
            ll x = min(a[i], e);
            ans += x;
            e -= x; a[i] -= x;
            ans += a[i] / 2ll * 6ll;
            if (a[i] % 2) ans += 5, e++;
        } else if (tp[i] == 'W') {
            if (!suf[i]) {
                a[i] -= min(a[i], e);
                ans += a[i] / 2ll * 4ll;
                if (a[i] % 2) ans += 3, e++;
                continue;
            }
            ll x = min(a[i], suf[i]);
            ans += x * 3ll;
            e += x; a[i] -= x;
        }
    }
    cout << ans;
    return 0;
}