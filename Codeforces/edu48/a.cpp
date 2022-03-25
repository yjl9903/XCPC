#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, m, a[maxn], cnt[maxn] = {0};

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int t = m;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        // while (x){
        //     if (t > x){
        //         t -= x;
        //         x = 0;
        //     }
        //     else {
        //         x -= t;
        //         cnt[i]++;
        //         t = m;
        //     }
        // }
        if (x < t){
            t -= x;
        }
        else {
            x -= t;
            cnt[i] = x / m + 1;
            t = m - x % m;
        }
        if (t == 0) t = m;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", cnt[i]);
    }
    return 0;
}