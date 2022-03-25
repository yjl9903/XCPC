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
const int maxn = 100000 + 5;

ll dp[maxn][2];
int n;

int main() {
    cin >> n;
    dp[1][0] = dp[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
        dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
    }
    ll sum = 0;
    for (int i = 1; i <= n; i++) sum += dp[i][0] + dp[i][1];
    cout << sum << endl;
    return 0;
}