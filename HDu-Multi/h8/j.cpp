#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, m, h[maxn], dp[maxn], sel[maxn], pre[maxn], c[maxn];

int st[maxn][35];
void init(){
    int l = 0;
    for (int i = 0; i < n; i++) st[i][0] = h[i];
    for (int j = 0; j < 31; j++) for (int i = 0; i + (1 << j) < n + 1; i++){
        st[i][j + 1] = max(st[i][j], st[i + (1 << j)][j]);
    }
}
int rmq(int l, int r){
    int m = (int)(log((r - l + 1) * 1.0) / log(2.0));
    return max(st[l][m], st[r - (1 << m) + 1][m]);
}
int get(int p, int v){
    int l = p + 1, r = n;
    while (l < r){
        int m = (l + r) / 2;
        if (rmq(p + 1, m) <= v) l = m + 1;
        else r = m;
    }
    return l;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%d", h + i);
        init();
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--){
            int p = get(i, h[i]);
            dp[i] = dp[p] + 1;
        }
        sel[0] = c[0] = 1;pre[0] = -1;
        int last = 0, lash = h[0], cnt = 1;
        for (int i = 1; i < n; i++){
            pre[i] = last;
            if (h[i] > lash){
                sel[i] = 1; last = i; lash = h[i];
                cnt++;
            }
            else sel[i] = 0;
            c[i] = cnt;
        }
        while (m--){
            int p, q; scanf("%d%d", &p, &q); p--;
            if (sel[p]){
                if (p == 0) {
                    int ans = 1 + dp[get(p, q)];
                    printf("%d\n", ans);
                }
                else {
                    if (q <= h[pre[p]]){
                        int ans = c[pre[p]] + dp[get(p, h[pre[p]])];
                        printf("%d\n", ans);
                    }
                    else {
                        int ans = c[p] + dp[get(p, q)];
                        printf("%d\n", ans);
                    }
                }
            }
            else {
                if (q <= h[pre[p]]){
                    printf("%d\n", cnt);
                }
                else {
                    int ans = c[pre[p]] + 1 + dp[get(p, q)];
                    printf("%d\n", ans);
                }
            }
        }
    }
    return 0;
}