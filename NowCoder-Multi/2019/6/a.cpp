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

char s[maxn], f[30];
int n;

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%s%s", s + 1, f);
        n = strlen(s + 1);
        int h = 0, w = 0, d = 0;
        for (int i = 1; i <= n; i++) {
            char tp = f[s[i] - 'a'];
            if (tp == 'h') h++;
            else if (tp == 'w') w++;
            else if (tp == 'd') d++;
        }
        printf("Case #%d: ", ++kase);
        if (h * 4 >= n) puts("Harmful");
        else if (h <= n / 10) puts("Recyclable");
        else {
            if (d >= 2 * w) puts("Dry");
            else puts("Wet");
        }
    }
    return 0;
}