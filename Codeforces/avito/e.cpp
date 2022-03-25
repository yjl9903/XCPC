#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n;
vector<int> fac[maxn * 2];
ll ans[maxn];

int main(){
    for (int i = 1; i < maxn * 2; i++) for (int j = i; j < maxn * 2; j += i)
        fac[j].push_back(i);
    scanf("%d", &n); 
    ll last = 0;
    for (int i = 2, x; i <= n; i += 2) {
        scanf("%d", &x);
        ll ansa = 1e18, ansb = 1e18;
        for (int d: fac[x]) {
            // a + b = x / d, b - a = d (a < b)
            ll a = x / d - d, b = x / d + d;
            if (a < 1 || b < 1 || a % 2 || b % 2 || a >= b) continue;
            a /= 2; b /= 2;
            if (a * a > last && b < ansb) {
                ansa = a; ansb = b;
            } 
        }
        if (ansa > 1e13) return puts("No"), 0;
        ans[i - 1] = ansa * ansa;
        ans[i] = last = ansb * ansb;
    }
    puts("Yes");
    for (int i = 1; i <= n; i++) printf("%lld ", ans[i] - ans[i - 1]);
    return 0;
}