#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;

int gcd(int a, int b){return b == 0 ? a : gcd(b, a % b);}
int n, m, step[maxn], factor[1000000], vis[1000000], num[1000000], cnt = 0;
ll res = 0;

int main(){
    int T, kase = 0; cin >> T;
    while (T--){
        cin >> n >> m; res = 0; cnt = 0; ms(vis, 0); ms(num, 0);
        for (int i = 0; i < n; i++) cin >> step[i];
        
        for (int i = 1; i * i <= m; i++){
            if (m % i == 0){
                factor[cnt++] = i;
                if (i * i != m) factor[cnt++] = m / i;
            }
        }
        sort(factor, factor + cnt);
        for (int i = 0; i < n; i++){
            int x = gcd(step[i], m);
            for (int i = 0; i < cnt - 1; i++) if (factor[i] % x == 0) vis[i] = 1;
        }

        for (int i = 0; i < cnt - 1; i++) if (vis[i] != num[i]){
            // cout << factor[i] << ' ' << num[i] << endl;
            // cout << 1ll * (factor[i] + m) * (m / factor[i]) / 2 - m << endl;
            // res += 1ll * ((factor[i] + m) * (m / factor[i]) / 2 - m) * (vis[i] - num[i]);
            res += 1ll * (m / factor[i]) * (m / factor[i] - 1) / 2 * factor[i] * (vis[i] - num[i]);
            for (int j = i + 1; j < cnt - 1; j++)
                if (factor[j] % factor[i] == 0)
                    num[j] += vis[i] - num[i];
        }
        
        cout << "Case #" << ++kase << ": ";
        cout << res << endl;
    }
    return 0;
}