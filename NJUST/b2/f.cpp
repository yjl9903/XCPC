#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int mx, my, n;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &mx, &my, &n);
        ll res = 0;
        for (int i = 0; i < n; i++){
            int x, y; scanf("%d%d", &x, &y);
            int t1 = min(x, mx - x), t2 = min(y, my - y);
            res += min(t1, t2);
        }
        printf("%lld\n", res);
    }
    return 0;
}