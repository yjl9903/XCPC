#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn];

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d", &n); for (int i = 0; i < n; i++) scanf("%d", a + i);
        int dp = a[0], op = 0, aop = 0, aed = 0, mx = dp;
        for (int i = 1; i < n; i++) {
            if (dp < 0) dp = a[i], op = i;
            else dp += a[i];
            if (dp > mx) mx = dp, aop = op, aed = i;
        }
        printf("Case %d:\n%d %d %d\n", ++kase, mx, aop + 1, aed + 1);
        if (T) puts("");
    }
    return 0;
}