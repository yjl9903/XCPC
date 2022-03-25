#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 2000000 + 5;
const int mod = 1e9 + 7;

int n, a[maxn], dp[maxn] = {1};

int main(){
    scanf("%d", &n); 
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    int f = 0, ans = 0;
    for (int i = 0; i < n; i++, f ^= 1){
        set<int> s;
        for (int j = 1; j * j <= a[i]; j++){
            if (a[i] % j) continue;
            s.insert(j); s.insert(a[i] / j);
        }
        for (auto it = s.rbegin(); it != s.rend(); it++){
            dp[*it] = (dp[*it] + dp[(*it) - 1]) % mod;
        }
    }
    for (int i = 1; i <= n; i++) ans = (ans + dp[i]) % mod;
    cout << ans;
    return 0;
}