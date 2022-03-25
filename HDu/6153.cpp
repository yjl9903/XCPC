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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

char s[maxn], t[maxn];

int n, m, ans[maxn], fail[maxn];
void getfail(int n, char s[]) {
    for (int i = 2; i <= n; i++) {
        int cur = fail[i - 1];
        while (cur && s[cur + 1] != s[i]) cur = fail[cur];
        if (s[cur + 1] == s[i]) cur++;
        fail[i] = cur;
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s%s", s + 1, t + 1);
        n = strlen(s + 1); m = strlen(t + 1);
        reverse(s + 1, s + 1 + n);
        reverse(t + 1, t + 1 + m);
        getfail(m, t);
        ms(ans, 0); int cur = 0;
        for (int i = 1; i <= n; i++) {
            while (cur && t[cur + 1] != s[i]) cur = fail[cur];
            if (t[cur + 1] == s[i]) cur++;
            ans[cur]++;
            if (cur == m) cur = fail[cur];
        }
        ll res = 0;
        for (int i = m; i >= 1; i--) ans[fail[i]] += ans[i];
        for (int i = 1; i <= m; i++) res += 1ll * i * ans[i];
        printf("%lld\n", res % mod);
    }
    return 0;
}