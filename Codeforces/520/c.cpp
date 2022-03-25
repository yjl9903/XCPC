#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const ll mod = 1e9 + 7;

char s[maxn];
int n, q, pre[maxn];
ll tw[maxn];

int main(){
    scanf("%d%d%s", &n, &q, s + 1); 
    tw[0] = 1; for (int i = 1; i <= n; i++) tw[i] = (tw[i - 1] + tw[i - 1]) % mod;
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + s[i] - '0';

    while (q--){
        int l, r; scanf("%d%d", &l, &r);
        int a = pre[r] - pre[l - 1], b = r - l + 1 - a;
        int ans = 1ll * (tw[a] - 1 + mod) % mod * tw[b] % mod;
        printf("%d\n", ans);
    }
    return 0;
}