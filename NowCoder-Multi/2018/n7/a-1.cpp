#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500000 + 5;

int n, a[maxn] = {0}, vis[maxn] = {0};

int main(){
    scanf("%d", &n);
    ll ss = 0, t = n, k = 0;
    while (t){
        t /= 2;
        ss = ss * 2 + 1;
    }
    for (int i = 0; i < n; i++) a[i] = i;
    
    for (ll i = n - 1; i >= 0;){
        ll x = ss - i;
        while (x < 0){
            ss <<= 1;
            x = ss - i;
        }
        // printf("%d %d\n", x, i);
        reverse(a + x, a + i + 1);
        ss >>= 1;
        i = x - 1;
    }

    printf("%d", a[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", a[i]);
    }
    return 0;
}