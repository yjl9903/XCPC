#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int maxp = 1e6 + 5;
const int mod = 1e9 + 7;

int prime[maxp], tot;
namespace sieve{
    bool vis[maxp];
    void init(){
        for (int i = 2; i < maxp; i++){
            if (!vis[i]) prime[tot++] = i;
            for (int j = 0; j < tot && prime[j] * i < maxp; j++){
                vis[i * prime[j]] = 1;
                if (i % prime[j] == 0) break;
            }
        }
    }
}

int b, n;
ll dp[maxn];
map<ll,int> mp;

int main(){
    sieve::init();
    scanf("%d%d", &b, &n);
    while (n--){
        ll x; scanf("%I64d", &x);
        for (int i = 0; i < tot && 1ll * prime[i] * prime[i] <= x; i++){
            if (x % prime[i]) continue;
            while (x % prime[i] == 0) x /= prime[i], mp[prime[i]]++;
        }
        if (x != 1) mp[x]++;
    }
    dp[1] = 1;
    for (auto& x : mp){
        int cnt = x.second;
        for (int i = b; i > 1; i--){
            for (int j = 1; j <= cnt; j++)
                if (i % (j + 1) == 0)
                    dp[i] = (dp[i] + dp[i / (j + 1)]) % mod;
        }
    }
    printf("%I64d\n", dp[b]);
    return 0;
}