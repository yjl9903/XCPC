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
const int maxn = 2000 + 5;

int n, m, k;
char s[maxn][maxn], ans[maxn][maxn];

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        for (int i = 0; i < n; i++) scanf("%s", s[i]);
        for (int i = 0; i < k * n; i++) {
            for (int j = 0; j < k * m; j++) {
                putchar(s[i / k][j / k]);
            }
            puts("");
        }
    }
    return 0;
}