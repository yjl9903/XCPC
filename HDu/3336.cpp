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
const int mod = 10007;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, fail[maxn], ans[maxn]; char s[maxn];

void getfail() {
    for (int i = 2; i <= n; i++) {
        int cur = fail[i - 1];
        while (cur > 0 && s[cur + 1] != s[i]) cur = fail[cur];
        if (s[cur + 1] == s[i]) cur++;
        fail[i] = cur;
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, s + 1);
        getfail();
        // for (int i = 1; i <= n; i++) cout << fail[i] << endl;
        ms(ans, 0);
        for (int i = 1; i <= n; i++) ans[fail[i]]++;
        for (int i = n; i >= 1; i--) {
            ans[fail[i]] += ans[i];
        }
        ll res = 0;
        for (int i = 1; i <= n; i++) res += 1 + ans[i];
        printf("%lld\n", res % mod);
    }
    return 0;
}