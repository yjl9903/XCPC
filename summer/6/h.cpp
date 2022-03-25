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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

void getfail(int len, int s[], int fail[]) {
    fail[1] = 0;
    for (int i = 2; i <= len; i++) {
        int cur = fail[i - 1];
        while (cur > 0 && s[cur + 1] != s[i])
            cur = fail[cur];
        if (s[cur + 1] == s[i])
            ++cur;
        fail[i] = cur;
    }
}

int n, m, p;
int a[maxn], b[maxn], fail[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &p);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i <= m; i++) scanf("%d", b + i);
        getfail(m, b, fail);
        int ans = 0;
        for (int t = 1; t <= p; t++) {
            int cur = 0;
            for (int i = t; i <= n; i += p) {
                while (cur > 0 && a[i] != b[cur + 1]) cur = fail[cur];
                if (a[i] == b[cur + 1]) cur++;
                if (cur == m) {
                    // ans = min(ans, i - (m - 1) * p);
                    ans++;
                    cur = fail[cur];
                }
            }
        }
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}