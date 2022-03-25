#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 3000000 + 5;

ll phi[maxn];
void phitable(int n){
    for(int i=2; i<=n; ++i)
        phi[i] = 0;
    phi[1] = 1;
    for(int i=2; i<=n; ++i) if((!phi[i]))
        for(int j=i; j<=n; j+=i){
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j]/i * (i-1);
        }
}

int main(){
    // phitable(100);
    // for (int i = 1; i <= 100; i++) printf("%d %d\n", i, phi[i]);
    int T; scanf("%d", &T);
    while (T--){
        int n; scanf("%d", &n);
        int res = 0;
        if (n == 1) res = 5;
        else res = n + 5;
        
        printf("%d\n", res);
    }
    return 0;
}