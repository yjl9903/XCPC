#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a, b, c[maxn];

int main(){
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 0; i < n; i++) scanf("%d", c + i);
    int ans = 0;
    if (n % 2 && c[n / 2] == 2) ans += min(a, b);
    for (int i = 0; i < n / 2; i++){
        if (c[i] == 2 && c[n - i - 1] == 2) ans += 2 * min(a, b);
        else if (c[i] == 2 || c[n - i - 1] == 2){
            int t = 0;
            if (c[i] != 2) t = c[i];
            if (c[n - i - 1] != 2) t = c[n - i - 1];
            if (t == 0) ans += a;
            else ans += b;
        }
        else {
            if (c[i] != c[n - i - 1]) {
                puts("-1"); return 0;
            }
        }
    }
    printf("%d", ans);
    return 0;
}