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

ll x;
ll dp[maxn];

int main() {
    cin >> x;
    dp[1] = dp[2] = 1; ll sum = 2;
    for (int i = 3; i <= 102; i++) {
        dp[i] = sum / 2; sum += dp[i];
        // cout << dp[i] << endl;
    }
    sum = 0;
    for (int i = 1; i <= 102; i++) {
        sum += dp[i];
        if (sum > x) {
            cout << i; return 0;
        }
    }
    return 0;
}