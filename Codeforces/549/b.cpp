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

int n;
char s[30], t[30];

ll cal(int x) {
    ll ans = 1;
    while (x) ans *= x % 10, x /= 10;
    return ans;
}

int main() {
    // cin >> n;
    cin >> s;
    if (strlen(s) == 1) return puts(s), 0;
    ll ans = 1;
    t[0] = s[0] - 1;
    for (int j = 1; s[j]; j++) t[j] = '9';
    for (int j = 0; t[j]; j++) {
        if (t[j] == '0') continue;
        ans *= t[j] - '0';
    }
    ll tot = 1;
    for (int i = 0; s[i]; i++) tot *= s[i] - '0';
    ans = max(tot, ans);
    for (int i = 1; s[i]; i++) {
        if (s[i] <= '1') continue;
        for (int j = 0; j < i; j++) t[j] = s[j];
        t[i] = s[i] - 1;
        for (int j = i + 1; s[j]; j++) t[j] = '9';
        ll tot = 1;
        for (int j = 0; t[j]; j++) {
            if (t[j] == '0') continue;
            tot *= t[j] - '0';
        }
        ans = max(ans, tot);
    }
    cout << ans << endl;
    return 0;
}