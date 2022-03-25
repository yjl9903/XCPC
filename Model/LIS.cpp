// PKu2533 Longest Ordered Subsequence

#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int inf = 1 << 30;

int a[maxn], dp[maxn], n;

int main(){
    while (cin >> n){
        for (int i = 1; i <= n; cin >> a[i++]);
        fill(dp, dp + 1 + n, inf);
        int res = 0;
        for (int i = 1; i <= n; i++){
            int p = lower_bound(dp + 1, dp + 1 + res, a[i]) - dp;
            dp[p] = a[i];
            res = max(p, res);
        }
        cout << res << endl;
    }
    return 0;
}