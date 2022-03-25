#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, k, a[maxn];

int dp[maxn][20];
void init(){
    for (int i = 0; i < n; i++) dp[i][0] = a[i];
    for (int j = 1; j < 20; j++) for (int i = 0; i + (1 << j) - 1 < n; i++)
        dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}
int rmq(int l, int r){
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1) k++;
    return max(dp[l][k], dp[r - (1 << k) + 1][k]);
}

bool check(int m){
    int c = n / m; ll s = 0;
    for (int i = 0; i + c - 1 < c * m; i += c){
        s += rmq(i, i + c - 1);
    }
    return s > 1.0 * k;
}

int main(){
    while (~scanf("%d%d", &n, &k)){
        if (n < 0 && k < 0) return 0;
        ll s = 0;
        for (int i = 0; i < n; i++) scanf("%d", a + i), s += a[i];
        if (s <= 1.0 * k){
            puts("-1"); continue;
        }
        init();
        int l = 1, r = n, ans = 0;
        while (l <= r){
            int m = (l + r) >> 1;
            if (check(m)) r = m - 1, ans = m;
            else l = m + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}

// 假的二分：
// 10 1500
// 1 1 1 1 1000 1000 1 1 1 1
//
// 8 201
// 100 100 100 100 101 100 100 100