#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

int n, m;
PII p[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%d%d", &p[i].second, &p[i].first);
        sort(p, p + n);
        ll s = 1;
        int res = 0;
        for (int i = 0; i < n; i++){
            s *= 1ll * (p[i].first + 1);
            if (s > 1ll * m){
                res = i; break;
            }
        }
        if (s <= 1ll * m) res = n;
        printf("%d\n", res);
    }
    return 0;
}