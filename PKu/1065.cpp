#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 5000 + 5;

int n, vis[maxn], dp[maxn];
PII p[maxn];

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n;
        for (int i = 0; i < n; i++){
            cin >> p[i].first >> p[i].second;
        }
        sort(p, p + n); ms(vis, 0);
        int res = 1;
        // for (int i = 0; i < n; i++){
        //     if (vis[i]) continue;
        //     int x = p[i].second;
        //     for (int j = i; j < n; j++){
        //         if (p[j].second >= x && !vis[j]){
        //             vis[j] = 1;
        //             x = p[j].second;
        //         }
        //     }
        //     res++;
        // }
        reverse(p, p + n);
        dp[1] = p[0].second;
        for (int i = 1; i < n; i++){
            if (p[i].second > dp[res]) dp[++res] = p[i].second;
            else {
                int k = lower_bound(dp + 1, dp + 1 + res, p[i].second) - dp;
                dp[k] = p[i].second;
            }
        }
        cout << res << endl;
    }
    return 0;
}