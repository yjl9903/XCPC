#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

PII st, ed, pre[maxn];
int n; char s[maxn];
ll totx, toty;

int check(ll x) {
    ll k = x / n, r = x % n;
    ll dx = k * pre[n].first + pre[r].first;
    ll dy = k * pre[n].second + pre[r].second;
    ll totx = st.first + dx, toty = st.second + dy;
    if (abs(totx - ed.first) + abs(toty - ed.second) <= x) return 1;
    else return 0;
}


int main() {
    scanf("%d%d%d%d%d%s", &st.first, &st.second, &ed.first, &ed.second, &n, s);
    int dx = 0, dy = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'U') dy++;
        if (s[i] == 'D') dy--;
        if (s[i] == 'L') dx--;
        if (s[i] == 'R') dx++;
        pre[i + 1] = {dx, dy};
    }
    // ll ans = -1;
    // for (int i = 0; i < n; i++) {
    //     totx = st.first + pre[i].first;
    //     toty = st.second + pre[i].second;
    //     ll l = 1, r = 1e9

    // }
    ll l = 1, r = 1e16, ans = -1;
    while (l <= r) {
        ll m = (l + r) / 2;
        if (check(m)) ans = m, r = m - 1;
        else l = m + 1; 
    }
    cout << ans << endl;
    return 0;
}   