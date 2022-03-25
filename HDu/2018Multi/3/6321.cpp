#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10 + 5;
const int inf = 1 << 11;
const int mod = 1000000007;

int n, m, dp[2][inf], ans[maxn], num[inf], sta[inf], cnt = 0;

inline void add(int& x, int y){
    x += y;
    if (x >= mod) x -= mod;
}
inline void sub(int& x, int y){
    x -= y;
    if (x < 0) x += mod;
}

int main(){
    int T; scanf("%d", &T);
    for (int i = 0; i < inf; i++){
        num[i] = num[i >> 1] + (i & 1);
        if (num[i] % 2 == 0) sta[cnt++] = i;
    }
    while (T--){
        scanf("%d%d", &n, &m);
        int ss = 1 << n, f = 0;
        ms(dp, 0); dp[0][0] = 1;
        while (m--){
            ms(ans, 0); getchar(); char ch = getchar();
            int x, y; scanf("%d%d", &x, &y); x--; y--;
            int tmp = (1 << x) | (1 << y);
            if (ch == '+'){
                for (int i = 0; i < cnt && sta[i] < ss; i++){
                    int s = sta[i];
                    dp[f ^ 1][s] = dp[f][s];
                    if ((tmp & s) == tmp) add(dp[f ^ 1][s], dp[f][s ^ tmp]);
                    add(ans[num[s] / 2], dp[f ^ 1][s]);
                }
            }
            else if (ch == '-'){
                for (int i = 0; i < cnt && sta[i] < ss; i++){
                    int s = sta[i];
                    dp[f ^ 1][s] = dp[f][s];
                    if ((tmp & s) == tmp) sub(dp[f ^ 1][s], dp[f][s ^ tmp]);
                    add(ans[num[s] / 2], dp[f ^ 1][s]);
                }
            }
            f ^= 1;
            for (int i = 1; i <= n / 2; i++) printf("%d%c", ans[i], i == n / 2 ? '\n' : ' ');
        }
    }
    return 0;
}