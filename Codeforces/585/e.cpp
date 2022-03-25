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
const ll inf = 1ll << 60;
const int maxn = 400000 + 5;

int n, a[maxn];
vector<int> pos[20];
ll dp[(1 << 20) + 5], cost[25][25];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        pos[a[i] - 1].push_back(i);
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == j || pos[j].empty()) continue;
            for (int x: pos[i]) {
                cost[i][j] += lower_bound(pos[j].begin(), pos[j].end(), x) - pos[j].begin();
            }
        }
    }
    int ss = 1 << 20;
    for (int s = 1; s < ss; s++) dp[s] = inf;
    for (int s = 0; s < ss; s++) {
        vector<int> v;
        for (int i = 0; i < 20; i++) {
            if (s >> i & 1) continue;
            v.push_back(i);
        }
        for (int x: v) {
            ll sum = dp[s];
            for (int y: v) sum += cost[x][y];
            dp[s | (1 << x)] = min(dp[s | (1 << x)], sum);
        }
    }
    cout << dp[ss - 1];
    return 0;
}