#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int maxd = 1e8 + 5;

struct node{
    int l, w, h;
    bool operator<(const node& b)const{
        return w > b.w;
    }
}a[maxn];

int n, d, dp[maxd];
// dp[i]: w<i -> maxh 
// w - -> restw + 
// restw >= i

int main(){
    scanf("%d%d", &n, &d);
    for (int i = 0; i < n; i++) scanf("%d%d%d", &a[i].l, &a[i].w, &a[i].h);
    sort(a, a + n); int ans = (a[0].l > d);
    for (int i = 1; i <= a[0].w; i++) dp[i] = a[0].h;
    for (int i = 1; i < n; i++){
        if (dp[a[i].w + 1] + a[i].l > d) ans++;
        for (int j = a[i].w; j >= 1; j--){
            dp[j] = max(dp[j], dp[j + 1]);
            dp[j] = max(dp[j], dp[j + a[i].w] + a[i].h);
            dp[j] = min(dp[j], (int)1e8);
        }
    }
    printf("%d\n", ans);
    return 0;
}