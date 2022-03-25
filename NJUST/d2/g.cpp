#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[20];

int main(){
    int kase = 0;
    while (~scanf("%d", &n) && n){
        int x = n, c = 0, k = 0;
        while (x % 2 == 0){
            c++; x /= 2;
        }
        if (c > 3){
            printf("Case %d: %d\n", ++kase, 0);
            continue;
        }
        while (x){
            a[k++] = x % 10;
            x /= 10;
            // printf("%d\n", a[k - 1]);
        }
        int flag = 0;
        for (int i = 0; i < k; i++){
            if (a[i] != 1){
                flag = 1; break;
            }
        }
        if (flag){
            printf("Case %d: %d\n", ++kase, 0);
            continue;
        }
        printf("Case %d: %d\n", ++kase, k);
    }
    return 0;
}