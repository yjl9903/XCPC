#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll m;
char s[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s%lld", s, &m);
        ll ans = 1, f = 1, x = 0;
        int len = strlen(s);
        if (len >= 7) x = m;
        else {
            for (int i = 0; i < len; i++) x = x * 10 + s[i] - '0';
        }
        for (ll i = 1; i <= x; i++){
            f = f * i % m;
            ans = (ans + f) % m;
        }
        printf("%lld\n", ans % m);
    }
    return 0;
}