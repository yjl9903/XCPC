#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;
const int inf = 1.5e7 + 10;

namespace sieve{
    int vis[inf], prime[inf], divsor[inf], tot = 0;
    void init(){
        ms(vis, 0);
        for (int i = 2; i < inf; i++){
            if (!vis[i]) prime[tot++] = i, divsor[i] = i;
            for (int j = 0; j < tot && prime[j] * i < inf; j++){
                vis[i * prime[j]] = 1; divsor[i * prime[j]] = prime[j];
                if (i % prime[j] == 0) break;
            }
        }
    }
}

int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
int n, a[maxn]; map<int,int> mp;

int main(){
    sieve::init();
    scanf("%d", &n); int g = 0;
    for (int i = 0; i < n; i++) scanf("%d", a + i), g = gcd(a[i], g);
    int one = 0;
    for (int i = 0; i < n; i++) {
        a[i] /= g; if (a[i] == 1) one++;
    }
    if (one == n){puts("-1"); return 0;}
    int ans = 0;
    for (int i = 0; i < n; i++){
        int x = a[i];
        while (x > 1){
            int t = sieve::divsor[x];
            mp[t]++; ans = max(ans, mp[t]);
            while (x % t == 0) x /= t;
        }
    }
    printf("%d", n - ans);
    return 0;
}