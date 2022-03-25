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

int check(int b, int s) {
    if (b == s) return 0;
    if (b == 0) return 0;
    if (s - b <= b) return 1;
    return 0;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        int n = strlen(s + 1), cnt = 0;
        for (int i = 2; i <= n; i++) if (s[i] == 'B') cnt++;
        printf("Case #%d: ", ++kase);
        if (cnt == 0 || cnt == n - 1) puts("N");
        else if (check(cnt, n - 1)) puts("Y");
        else {
            if (cnt == 1) {
                if (n == 3) puts("Y");
                else puts("N");
            } else if (cnt == 0) puts("N");
            else puts("Y");
        }
    }
    return 0;
}