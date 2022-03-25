#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n;

int main(){
    scanf("%I64d", &n);
    int ans = 0;
    for (int i = 0; i < 33; i++){
        if (n > (1ll << i)) n -= (1ll << i), ans++;
        else break;
    }
    if (n) ans++;
    printf("%d", ans); 
    return 0;
}