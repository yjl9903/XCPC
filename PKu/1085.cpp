#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;
const int maxm = 10 + 5;

int n, m, map[maxn] = {0}, dp[maxn][10 * maxm][10 * maxm] = {0}; // dp[i][now][pre]
int st[maxn][10 * maxm], len[maxn] = {0};

bool check(int s){
    if (s & (s << 1)) return false;
    if (s & (s << 2)) return false;
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        char s[maxm]; cin >> s;
        for (int j = 0; j < m; j++){
            if (s[j] == 'H') map[i] = map[i] | (1 << j); // 山地 1
        }
    }

    int ss = (1 << m) - 1, res = 0; ms(dp, 0);
    for (int i = 0; i <= n; i++){
        int l = 0;
        for (int s = 0; s <= ss; s++) if ((s & map[i]) == 0 && check(s)) st[i][l++] = s;
        len[i] = l;
    }
    
    // for (int s = 0; s <= ss; s++) if ((s & map[1]) == 0 && check(s)){
    for (int i = 0; i < len[1]; i++) {
        int t = 0, s = st[1][i];
        for (int j = 0; j < m; j++) if (s & (1 << j)) t++;
        // for (int s2 = 0; s2 <= ss; s2++) dp[1][s][s2] = t;
        for (int j = 0; j < len[0]; j++) dp[1][i][j] = t;
        res = max(t, res);
    }
    for (int i = 2; i <= n; i++){
        // for (int s = 0; s <= ss; s++) if ((s & map[i]) == 0 && check(s)){
        for (int j = 0; j < len[i]; j++){
            int t = 0, s = st[i][j];
            for (int k = 0; k < m; k++){
                if (s & (1 << k)) t++;
            }
            // for (int s2 = 0; s2 <= ss; s2++) if ((s2 & map[i - 1]) == 0 && check(s2) && (s2 & s) == 0){
            for (int k = 0; k < len[i - 1]; k++) {
                int s2 = st[i - 1][k];
                if (s2 & s) continue;
                // for (int s3 = 0; s3 <= ss; s3++) if ((s3 & map[i - 2]) == 0 && check(s3) && (s3 & s) == 0 && (s3 & s2) == 0){
                for (int l = 0; l < len[i - 2]; l++){
                    int s3 = st[i - 2][l];
                    if (s3 & s) continue;
                    if (s3 & s2) continue;
                    // dp[i][s][s2] = max(dp[i - 1][s2][s3] + t, dp[i][s][s2]);
                    dp[i][j][k] = max(dp[i - 1][k][l] + t, dp[i][j][k]);
                }
                // res = max(res, dp[i][s][s2]);
                res = max(res, dp[i][j][k]);
            }
        }
    }
    
    cout << res << endl;
    return 0;
}