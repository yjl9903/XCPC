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

char a[maxn], b[maxn], c[maxn];
int n, m;
char f[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%s%s%s", &n, &m, a + 1, b + 1, c + 1);
        int offset = (a[1] - b[1] + 26) % 26;
        for (int i = 1; i <= m; i++) {
            c[i] = (c[i] - 'A' + offset) % 26 + 'A';
        }
        printf("Case #%d: ", ++kase);
        puts(c + 1);
    }
    return 0;
}