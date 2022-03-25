#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, res, l, r, dp[maxn][15], tot;
char a[maxn], b[20];

int cal(){
    ms(dp[0], 0);
    for (int i = 0; i < n; i++){
        int* pre = dp[i], *cur = dp[i + 1];
        for (int j = 0; j < tot; j++){
            cur[j] = pre[j] + (a[i] == b[j]);
            if (j && cur[j] < cur[j - 1]) cur[j] = cur[j - 1];
        }
    }
    return dp[n][tot - 1];
}

void get(char x, char y){
    int tl = 0, tr = 0;
    for (int i = n - 1, j = tot - 1; i >= 0; i--){
        int *pre = dp[i], *cur = dp[i + 1];
        int lf = pre[j] + (a[i] == b[j]);
        int rf = j ? cur[j - 1] : -1;
        while (lf < rf){
            if (b[j - 1] == x && b[j] == y){
                if (!tr) tr = i;
                else tl = i + 1;
            }
            j--;
            lf = pre[j] + (a[i] == b[j]);
            rf = j ? cur[j - 1] : -1;
        }
    }
    l = tl + 1; r = tr + 1;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%s", &n, a);
        char vl = '9', vr = '0';
        for (int i = 0; i < n; i++){
            vl = min(vl, a[i]);
            vr = max(vr, a[i]);
        }
        if (vl == vr){
            printf("%d 1 1\n", n);
            continue;
        }
        res = 0, l = 0, r = 0;
        for (char i = vl; i < vr; i++){
            for (char j = i + 1; j <= vr; j++){
                tot = 0;
                for (char ch = vl; ch <= i; ch++) b[tot++] = ch;
                for (char ch = j; ch >= i; ch--) b[tot++] = ch;
                for (char ch = j; ch <= vr; ch++) b[tot++] = ch;
                int t = cal();
                if (t > res){
                    res = t;
                    get(i, j);
                }
            }
        }
        printf("%d %d %d\n", res, l, r);
    }
    return 0;
}