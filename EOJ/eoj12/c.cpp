#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 4000 + 5;
const ll mod = 1e9 + 7;

int gi(){
    char ch = getchar(); int r = 0;
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') r = r * 10 + ch - '0', ch = getchar();
    return r;
}

int f[maxn], inv[maxn], finv[maxn];
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1; 
    for (int i = 1; i < maxn; i++) {
        f[i] = f[i - 1] * 1ll * i % mod;
        finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
}
int C(int n, int m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}

int n, q, cnt[maxn][10]; char s[maxn];
// vector<int> pos[100], ans[100];
int pos[100][maxn], ans[100][maxn], len[100]; 
ll rec[maxn][100];

int main(){
    init(); ms(rec, -1);
    // scanf("%s%d", s + 1, &q); n = strlen(s + 1);
    scanf("%s", s + 1); n = strlen(s + 1); q = gi();

    for (int i = n; i >= 1; i--){
        cnt[i][s[i] - '0']++;
        for (int j = 0; j < 10; j++) cnt[i][j] += cnt[i + 1][j];
    }
    for (int i = 0; i <= 99; i++){
        int x = i / 10, y = i % 10, l = 0;
        for (int j = 1; j <= n; j++){
            if (s[j] - '0' == x && cnt[j + 1][y]){
                // pos[i].push_back(j - 1);
                // ans[i].push_back(cnt[j + 1][y]);
                pos[i][l] = j - 1;
                ans[i][l] = cnt[j + 1][y];
                l++;
            }
            len[i] = l;
        }
    }

    while (q--){
        int m, xy; 
        // scanf("%d%d", &m, &xy);
        m = gi(); xy = gi();
        if (m > n || m == 1) {
            puts("0"); continue;
        }
        if (rec[m][xy] != -1) {
            printf("%lld\n", rec[m][xy]);
            continue;
        }
        ll res = 0;
        // for (int i = 0; i < pos[xy].size(); i++){
        //     res += 1ll * C(pos[xy][i], m - 2) * ans[xy][i] % mod;
        //     res %= mod;
        // }
        for (int i = 0; i < len[xy]; i++) {
            res += 1ll * C(pos[xy][i], m - 2) * ans[xy][i] % mod;
            if (res >= mod) res -= mod;
        }
        rec[m][xy] = res;
        printf("%lld\n", res);
    }
    return 0;
}