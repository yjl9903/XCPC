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
const int maxn = 1000 + 5;

int n, f[maxn][maxn]; char s[maxn];

void add(int& x, int y) {
    x += y; if (x >= mod) x -= mod;
}
void sub(int& x, int y) {
    x -= y; if (x < 0) x += mod;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1); n = strlen(s + 1);
        ms(f, 0); for (int i = 1; i <= n; i++) f[i][i] = 1;
        for (int len = 2; len <= n; len++) {
            for (int l = 1; l + len - 1 <= n; l++) {
                int r = l + len - 1;
                add(f[l][r], f[l + 1][r]);
                add(f[l][r], f[l][r - 1]);
                sub(f[l][r], f[l + 1][r - 1]);
                if (s[l] == s[r]) add(f[l][r], f[l + 1][r - 1] + 1);
            }
        }
        printf("Case %d: %d\n", ++kase, f[1][n]);
    }
    return 0;
}