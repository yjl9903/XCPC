#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

int gcd(int a, int b){return b ? gcd(b, a % b) : a;}

int n, a[maxn], b[maxn]; map<PII,int> mp;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    int cnt = 0, ans = 0, mp0 = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0 && b[i] == 0) cnt++;
        else if (b[i] == 0) mp0++;
        else if (a[i] == 0) ;
        else {
            if (1ll * a[i] * b[i] > 0) {
                int g = gcd(abs(a[i]), abs(b[i]));
                mp[{abs(a[i]) / g, abs(b[i]) / g}]++;
            } else {
                int g = gcd(abs(a[i]), abs(b[i]));
                mp[{-abs(a[i]) / g, abs(b[i]) / g}]++;
            }
        }
    }
    ans = mp0;
    for (auto& x: mp) ans = max(ans, x.second);
    cout << ans + cnt << endl;
    return 0;
}