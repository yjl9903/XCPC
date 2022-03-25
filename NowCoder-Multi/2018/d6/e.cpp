#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

vector<int> v1, v2;
int n, m, z[maxn], a[maxn][maxn];
PII p[maxn];
ll dp[maxn][maxn], pre1[maxn][maxn], pre2[maxn][maxn], pre3[maxn][maxn];

int main(){
    scanf("%d%d", &n, &m);
    v1.push_back(0); v2.push_back(0);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &p[i].first, &p[i].second, z + i);
        v1.push_back(p[i].first), v2.push_back(p[i].second);
    }
    sort(v1.begin(), v1.end()); sort(v2.begin(), v2.end());
    v1.resize(unique(v1.begin(), v1.end()) - v1.begin());
    v2.resize(unique(v2.begin(), v2.end()) - v2.begin());
    ll sum = 0;
    for (int i = 1; i <= n; i++){
        int x = lower_bound(v1.begin(), v1.end(), p[i].first) - v1.begin();
        int y = lower_bound(v2.begin(), v2.end(), p[i].second) - v2.begin();
        a[x][y] += z[i];
    }
    
    for (int i = 1; i < v1.size(); i++)
        for (int j = 1; j < v2.size(); j++)
            pre1[i][j] = pre1[i][j - 1] + a[i][j];
    for (int i = 1; i < v2.size(); i++)
        for (int j = 1; j < v1.size(); j++)
            pre2[j][i] = pre2[j - 1][i] + a[j][i];
    for (int i = 1; i < v1.size(); i++)
        for (int j = 1; j < v2.size(); j++)
            pre3[i][j] = pre3[i - 1][j] + pre1[i][j];

    // for (int i = 1; i < v1.size(); i++, puts(""))
    //     for (int j = 1; j < v2.size(); j++)
    //         cout << pre1[i][j] << ' ';
    // puts("");
    // for (int i = 1; i < v1.size(); i++, puts(""))
    //     for (int j = 1; j < v2.size(); j++)
    //         cout << pre3[i][j] << ' ';
    // puts("");

    ll ans = 0; int px = 0, py = 0;
    for (int i = 1; i < v1.size(); i++){
        for (int j = 1; j < v2.size(); j++){
            // if (v1[i] + v2[j] > m) break;
            ll x = dp[i - 1][j] + 1ll * (v1[i] - v1[i - 1] - 1) * pre3[i - 1][j] + pre3[i][j];
            ll y = dp[i][j - 1] + 1ll * (v2[j] - v2[j - 1] - 1) * pre3[i][j - 1] + pre3[i][j];
            // cout << x - pre1[i][j] << ' ' << y - pre2[i][j] << endl;
            // printf("%d %d %lld %lld\n", v1[i], v2[j], x, y);
            dp[i][j] = max(x, y);
            if (m >= v1[i] + v2[j])
                ans = max(ans, dp[i][j] + 1ll * (m - v1[i] - v2[j]) * pre3[i][j]);
        }
    }
    // ans = dp[v1.size() - 1][v2.size() - 1];
    // if (m >= v1.back() + v2.back()) ans += sum * (m - v1.back() - v2.back());
    printf("%lld", ans);
    return 0;
}