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
const int maxn = 100000 + 5;

char s[maxn]; int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, s + 1);
        int ans = n;
        for (int i = 1; i <= n; i++) if (s[i] == '>') {ans = min(ans, i - 1); break;}
        reverse(s + 1, s + n + 1);
        for (int i = 1; i <= n; i++) if (s[i] == '<') {ans = min(ans, i - 1); break;}
        printf("%d\n", ans);
    }
    return 0;
}