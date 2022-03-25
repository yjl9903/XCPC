#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int a[maxn], n;

int main(){
    while (~scanf("%d", &n) && n){
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        ll res = 0;
        int j = 0;
        while (a[j] >= 0) j++;
        for (int i = 0; i < n; i++){
            if (a[i] <= 0) continue;
            // printf("%d %d\n", i, j);
            while (a[i] + a[j] > 0 && i < n && j < n){
                res += 1ll * abs(i - j) * abs(a[j]);
                a[i] = a[i] + a[j];
                a[j] = 0;
                while (a[j] >= 0 && j < n) j++;
            }
            res += 1ll * abs(i - j) * a[i];
            a[j] = a[j] + a[i];
            a[i] = 0;
            while (a[j] >= 0 && j < n) j++;
        }
        printf("%lld\n", res);
    }
    return 0;
}