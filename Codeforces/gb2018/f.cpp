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

int n;
ll l[maxn];
char s[maxn];

int main(){
    scanf("%d", &n); 
    for (int i = 1; i <= n; i++) scanf("%I64d", l + i);
    scanf("%s", s + 1);
    ll ans = 0, sum = 0, tg = 0, tw = 0;
    int isw = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'G') {
            sum += l[i];
            tg += 2 * l[i];
            ans += 5 * l[i];
        } else if (s[i] == 'W') {
            sum += l[i];
            ans += 3 * l[i];
            isw = 1;
        } else {
            if (sum < l[i]) {
                if (isw) {
                    ans += 3 * (l[i] - sum);
                }
                else {
                    ans += 5 * (l[i] - sum);
                }
                sum = l[i];
            } 
            sum -= l[i];
            ans += l[i];
        }
        tg = min(sum, tg);
    }
    if (sum > 0) {
        ans -= 4 * tg / 2;
        ans -= 2 * (sum - tg) / 2;
    }
    // sum /= 2;
    // ans -= 4 * min(sum, tg);
    // sum -= min(sum, tg);
    // ans -= 2 * min(sum, tw);
    cout << ans;
    return 0;
}