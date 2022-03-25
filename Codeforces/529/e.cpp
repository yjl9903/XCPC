#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int n, pre[maxn], isp[maxn], suf[maxn], iss[maxn]; char s[maxn];

int main(){
    scanf("%d%s", &n, s + 1);
    isp[0] = iss[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1];
        if (s[i] == '(') pre[i]++;
        else pre[i]--;
        if (pre[i] >= 0 && isp[i - 1]) isp[i] = 1;
    }
    for (int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1];
        if (s[i] == '(') suf[i]++;
        else suf[i]--;
        if (suf[i] <= 0 && iss[i + 1]) iss[i] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!isp[i - 1] || !iss[i + 1]) continue;
        if (s[i] == '(') {
            if (/* pre[i - 1] > 0 &&  */pre[i - 1] + suf[i + 1] - 1 == 0) ans++;
        } else {
            if (pre[i - 1] + suf[i + 1] + 1 == 0) ans++;
        }
    }
    cout << ans;
    return 0;
}