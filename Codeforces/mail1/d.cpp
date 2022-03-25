#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, k, a[maxn];
map<int,int> mp;

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    int s = 0; mp[0] = 1;
    for (int i = 0; i < n; i++){
        int p = s ^ a[i], q = s ^ ((1 << k) - 1 - a[i]);
        if (mp[p] <= mp[q]) mp[s = p]++;
        else mp[s = q]++;
    }
    ll ans = 1ll * n * (n + 1) / 2;
    for (auto& x : mp){
        int c = x.second;
        ans -= 1ll * c * (c - 1) / 2;
    }
    printf("%I64d", ans);
    return 0;
}