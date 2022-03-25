#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <unordered_map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 1000000 + 5;

int n, m, q, suf[maxn];
char s[maxn];
int mp[(int)5e7 + 5];

int main() {
    scanf("%s%d", s, &q); n = strlen(s);
    while (q--) {
        scanf("%d", &m);
        suf[n] = 0; mp[0] = n;
        int flag = 1, tot = 1;
        for (int i = n - 1; i >= 0; i--, tot = tot * 10 % m) {
            suf[i] = (suf[i + 1] + 1ll * (s[i] - '0') * tot) % m;
            if (mp[suf[i]]) {
                printf("%d %d\n", i + 1, mp[suf[i]]);
                flag = 0; break;
            }
            mp[suf[i]] = i;
        }
        if (flag) puts("-1");
        for (int i = 0; i <= m; i++) mp[i] = 0;
    }
    return 0;
}