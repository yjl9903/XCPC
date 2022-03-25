#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int L, v, l, r;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d%d", &L, &v, &l, &r);
        int t1 = l / v, t2 = r / v, ans = L / v;
        if (l % v == 0) t1--;
        // if (r % v) t2++;
        // for (int i = v; i <= L; i += v){
        //     if (l <= i && i <= r) {}
        //     else ans++;
        // }
        printf("%d\n", ans - t2 + t1);
    }
    return 0;
}