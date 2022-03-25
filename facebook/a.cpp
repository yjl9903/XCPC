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

char s[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        int n = strlen(s + 1), cnt = 0;
        for (int i = 2; i <= n; i++) if (s[i] == 'B') cnt++;
        int rest = n - cnt - 1;
        printf("Case #%d: ", ++kase);
        if (rest <= cnt && rest) puts("Y");
        else puts("N");
    }
    return 0;
}