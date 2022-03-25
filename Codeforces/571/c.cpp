#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
// #include <bitset>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;
const int sz = 1000 + 5;

char s[maxn], t[maxn];
int n, m, pre[maxn];

int main() {
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1); m = strlen(t + 1);
    for (int i = 2; i <= n; i++) {
        pre[i] = pre[i - 1];
        if (s[i] != s[i - 1]) pre[i]++;
    } pre[n + 1] = pre[n];
    int ans = 0, tot = 0;
    for (int i = 1; i <= m; i++) if (s[i] != t[i]) tot ^= 1;
    if (tot == 0) ans++;
    for (int i = m + 1; i <= n; i++) {
        // int f = pre[i + 1] - pre[i - m + 1];
        tot ^= (pre[i] - pre[i - m]) % 2;
        if (tot == 0) ans++;
    }
    cout << ans;
    return 0;
}