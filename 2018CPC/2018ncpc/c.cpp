#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, x, vis[maxn];

int main(){
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++) scanf("%d", &x), vis[x] = 1;
    int ans = 0, tot = 0, cnt = 0;
    for (int i = 1; i <= 365; i++){
        if (vis[i]) cnt++;
        tot += cnt;
        if (tot >= 20){
            ans++; tot = 0; cnt = 0;
        }
    }
    if (tot) ans++;
    printf("%d\n", ans);
    return 0;
} 