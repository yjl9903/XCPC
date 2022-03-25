#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, c, a[maxn], b[maxn];
ll dp[maxn][2];

int main() {
    scanf("%d%d", &n, &c);
    for (int i = 1; i < n; i++) scanf("%d", a + i);
    for (int i = 1; i < n; i++) scanf("%d", b + i);
    printf("0"); dp[0][1] = c;
    for (int i = 1; i < n; i++) {
        dp[i][0] = a[i] + min(dp[i - 1][0], dp[i - 1][1]);
        dp[i][1] = min(dp[i - 1][0] + c + b[i], dp[i - 1][1] + b[i]);
        printf(" %I64d", min(dp[i][0], dp[i][1]));
    }
    return 0;
}