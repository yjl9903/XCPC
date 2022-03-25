#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, k;

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &n, &m,&k);
        // double ans1 = 0, ans2 = 1.0;
        // for (int i = 0; i < k; i++) ans2 *= double(m - i) / double(n - i);
        // for (int i = 0; i < k; i++){
        //     double q = 1.0 - double(m - i) / double(n - i);
            
        // }
        // cout << ans1 << ' ' << ans2 << endl;
        // printf("%lf\n", ans1 * ans2);
        double q = 1 - double(m) / double(n), ans = double(m) / double(n) * (1.0 / double(1 - q) / double(1 - q));
        for (int i = 1; i < k; i++){
            q = 1 - double(m - i) / double(n - i);
            ans = ans / double(1 - q) + 1.0 / double(1 - q) / double(1 - q);
            ans *= double(m - i) / double(n - i);
        }
        printf("Case #%d: %.7lf\n", ++kase, ans);
    }
    return 0;
}