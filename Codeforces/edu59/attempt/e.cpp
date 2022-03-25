#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200 + 5;

int n, a[maxn], v[maxn];
char s[maxn];
vector<int> p;

int f[maxn][maxn];
int dp(int l, int r) {
    if (f[l][r]) return f[l][r];
    if (l > r) return 0;
    if (l == r) return f[l][r] = v[p[l]];
    int ans = v[p[l]] + dp(l + 1, r);
    for (int i = l + 2; i <= r; i += 2) {
        int tot = v[p[l] + p[i]] + dp(l + 1, i - 1) + dp(i + 1, r);
        ans = max(ans, tot);
        // ans = max(ans, dp(l, i) + dp(i + 1, r));
    }
    return f[l][r] = ans;
}

int main(){
    scanf("%d%s", &n, s + 1);
    int last = 1;
    for (int i = 2; i <= n; i++) {
        if (s[i] != s[i - 1]) {
            p.push_back(i - last); last = i;
        }
    }
    p.push_back(n + 1 - last);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) {
        v[i] = a[i];
        for (int j = 1; j < i; j++) v[i] = max(v[i], v[j] + v[i - j]);
    }
    cout << dp(0, p.size() - 1) << endl;
    for (int i = 0; i < n; i++, puts("")) for (int j = 0; j < n; j++) printf("%d ", f[i][j]);
    return 0;
}