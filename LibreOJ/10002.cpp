#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<double,double> P;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, l, w;
P a[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &n, &l, &w);
        for (int i = 0, p, r; i < n; i++) {
            scanf("%d%d", &p, &r);
            double x = 0; 
            if (1.0 * r * r - 1.0 * w * w / 4.0 >= 0) x = sqrt(1.0 * r * r - 1.0 * w * w / 4.0);
            a[i].first = 1.0 * p - x;
            a[i].second = 1.0 * p + x;
        }
        sort(a, a + n, [](P a, P b) { return a.first != b.first ? a.first < b.first : a.second < b.second; });
        // for (int i = 0; i < n; i++) {
        //     cout << a[i].first << ' ' << a[i].second << endl;
        // }
        int ans = 0, flag = 0, i = 0; double r = 0;
        while (r < l) {
            ans++;
            double t = r; int f = 0;
            while (i < n && a[i].first <= t) {
                if (a[i].second > r) r = a[i].second, f = 1;
                i++;
            }
            if (!f && r < l) {
                flag = 1; break;
            }
        }
        if (flag) puts("-1");
        else printf("%d\n", ans);
    }
    return 0;
}