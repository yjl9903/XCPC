#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;

int n, a[maxn];

bool get(int avg){
    ll s1 = 0, s2 = 0;
    for (int i = 0; i < n; i++)
        if (a[i] < avg) s1 += avg - a[i];
        else if (a[i] > avg) s2 += (a[i] - avg) / 2;
    return s1 <= s2;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        int res = 0, l = 0, r = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            r = max(r, a[i]);
        }
        if (n == 1){
            printf("%d\n", a[0]); continue;
        }
        while (l <= r){
            int m = (l + r) / 2;
            if (get(m)){
                res = m; l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}