#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, m, p[maxn], a[maxn]; ll t;

int check(int x){
    int d = a[x], cnt = 0; ll s = 0, last = 0;
    for (int i = 1; i <= n && cnt < x; i++){
        if (p[i] > d) continue;
        if (cnt && cnt % m == 0){
            s += last; last = 0;
        }
        s += p[i]; last += p[i]; cnt++;
    }
    return s <= t;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%I64d", &n, &m, &t);
        for (int i = 1; i <= n; i++) scanf("%d", p + i), a[i] = p[i];
        sort(a + 1, a + n + 1);
        int l = 1, r = n, ans = 0;
        while (l <= r){
            int m = l + r >> 1; 
            if (check(m)) l = m + 1, ans = m;
            else r = m - 1;
        }
        if (r) printf("%d %d\n", ans, a[ans]);
        else printf("%d %I64d\n", 0, t);
    }
    return 0;
}