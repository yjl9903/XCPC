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

int n, a[maxn], b[maxn];

struct ST {
    int dp[maxn][20];
    void build(int* a) {
        for (int i = 1; i <= n; i++) dp[i][0] = i;
        for (int j = 1; j < 20; j++)
            for (int i = 1; i + (1 << j) <= n + 1; i++) {
                int p1 = dp[i][j - 1], p2 = dp[i + (1 << (j - 1))][j - 1];
                if (a[p1] < a[p2]) dp[i][j] = p1;
                else dp[i][j] = p2;
            }
    }
    int query(int* a, int l, int r) {
        int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
        int p1 = dp[l][k], p2 = dp[r - (1 << k) + 1][k];
        return a[p1] < a[p2] ? p1 : p2;
    }
} f, g;

int flag;
void solve(int l, int r) {
    if (l >= r) return ;
    if (!flag) return ;
    int p1 = f.query(a, l, r), p2 = g.query(b, l, r);
    if (p1 != p2) {
        flag = 0; return ;
    }
    solve(l, p1 - 1); solve(p1 + 1, r);
}
int check(int x) {
    flag = 1;
    solve(1, x);
    return flag;
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i <= n; i++) scanf("%d", b + i);
        f.build(a); g.build(b);
        int l = 1, r = n, ans = 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (check(m)) ans = m, l = m + 1;
            else r = m - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}