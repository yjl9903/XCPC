#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m, a[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m); int cnt = 0; vector<int> v;
        for (int i = 0; i < n; i++){
            scanf("%d", a + i);
            if (!a[i]) cnt++;
            else v.push_back(a[i]);
        }
        if (n == m) puts("Richman");
        else if (cnt > m) puts("Impossible");
        else {
            m -= cnt;
            ll sum = 0, mn = v[m]; 
            for (int i = 0; i < m; i++) sum += v[i];
            for (int i = m; i < v.size(); i++) mn = min(mn, 1ll * v[i]);
            printf("%lld\n", sum + max(mn - 1, 0ll));
        }
    }
    return 0;
}