#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, a[maxn];

int main(){
    while (~scanf("%d", &n)){
        for (int i = 0; i <= n; i++) scanf("%d", &a[i]);
        int s = 0, res = 0;
        for (int i = n; i >= 0; i--){
            s += a[i];
            if (s >= i){
                res = i; break;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}