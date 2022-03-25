#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

PII a[maxn];
int dp[maxn];

int main(){
    int x, y, cnt;
    while (cin >> x >> y){
        if (x == -1 && y == -1) break;
        a[0].first = x; a[0].second = y;
        cnt = 1;
        while (cin >> x >> y){
            if (!x && !y) break;
            a[cnt].first = x; a[cnt].second = y;
            cnt++;
        }
        sort(a, a + cnt); reverse(a, a + cnt);
        int res = 1;
        dp[1] = a[0].second;
        for (int i = 1; i < cnt; i++){
            if (a[i].second > dp[res]) dp[++res] = a[i].second;
            else {
                int k = lower_bound(dp + 1, dp + 1 + res, a[i].second) - dp;
                dp[k] = a[i].second;
            }
        }
        cout << res << endl;
    }
    return 0;
}