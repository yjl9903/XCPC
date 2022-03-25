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
typedef pair<double,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n;
string s[maxn];
char tmp[maxn];
int ps, sh, suf[maxn];
vector<PII> v;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", tmp);
        s[i] = string(tmp);
        int len = strlen(tmp), c1 = 0, c2 = 0;
        for (int i = 0; i < len; i++) if (tmp[i] == 's') c1++; else if (tmp[i] == 'h') c2++;
        if (c1 == len) ps += len;
        else if (c2 == len) sh += len;
        else v.push_back({(double)c2 / (double)c1, i});
    }
    sort(v.begin(), v.end());
    string str;
    for (auto& x: v) str += s[x.second];
    suf[str.length()] = sh;
    for (int i = str.length() - 1; i >= 0; i--) suf[i] = suf[i + 1] + (int)(str[i] == 'h');
    ll ans = 1ll * ps * suf[0];
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == 'h') continue;
        ans += suf[i];
    }
    cout << ans << endl;
    return 0;
}