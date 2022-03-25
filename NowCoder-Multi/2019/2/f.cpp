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
const int maxn = 30 + 5;
 
int n, G[maxn][maxn];
 
ll ans, tot;
vector<int> stk, stk2;
void dfs(int now, int cnt) {
    if (cnt == n) {
        ll tot2 = tot;
        for (int i = now; i <= 2 * n; i++) {
            for (int x: stk2) tot2 -= G[x][i];
            stk2.push_back(i);
        }
        // cout << tot2 << endl;
        for (int i = now; i <= 2 * n; i++) stk2.pop_back();
        ans = max(ans, tot2);
        return ;
    }
    if (2 * n - now + 1 < n - cnt) return ;
 
    for (int x: stk2) tot -= G[x][now];
    stk2.push_back(now);
    dfs(now + 1, cnt);
    stk2.pop_back();
    for (int x: stk2) tot += G[x][now];
     
    for (int x: stk) tot -= G[x][now];
    stk.push_back(now);
    dfs(now + 1, cnt + 1);
    stk.pop_back();
    for (int x: stk) tot += G[x][now];
}
 
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 1; j <= 2 * n; j++) {
            scanf("%d,", &G[i][j]);
        }
        for (int j = 1; j < i; j++) tot += G[i][j];
    }
    stk.push_back(1);
    dfs(2, 1);
    cout << ans << '\n';
    return 0;
}