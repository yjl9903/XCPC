#include <iostream>
#include <cstdio>
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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int query(ll x) {
    cout << x << endl;
    char s[10]; cin >> s;
    if (s[0] == 'b') return 1;
    else if (s[0] == 's') return -1;
    else return 0;
}

int main() {
    ll l = -1e9, r = 1e9, ans = -1;
    while (l <= r) {
        ll m = (l + r) / 2;
        int re = query(m);
        if (re == 0) break;
        if (re == 1) r = m - 1;
        else l = m + 1;
    }
    return 0;
}