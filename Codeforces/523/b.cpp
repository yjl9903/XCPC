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
    scanf("%d%*d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    sort(a + 1, a + 1 + n);
    int mx = 0, rest = 0; ll ans = 0;
    for (int i = 1; i <= n; i++){
        if (a[i] > mx) ans += mx, rest += a[i] - mx - 1, mx = a[i];
        else if (a[i] > 1){
            if (rest) ans += a[i], rest--;
            else ans += a[i] - 1;
        }
    }
    cout << ans;
    return 0;
}