#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;



int main() {
    int T; scanf("%d", &T);
    while (T--) {
        string a, b;
        cin >> a >> b;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        ll x = 0, y = 0;
        for (int i = 0; i < a.length(); i++) x = x * 10ll + (a[i] - '0');
        for (int i = 0; i < b.length(); i++) y = y * 10ll + (b[i] - '0');
        // cout << x << ' ' << y << endl;
        x += y;
        string ans;
        while (x) {
            ans += x % 10 + '0'; x /= 10;
        }
        ll res = 0;
        for (int i = 0; i < ans.length(); i++) res = res * 10ll + (ans[i] - '0');
        cout << res << '\n';
    }
    return 0;
}