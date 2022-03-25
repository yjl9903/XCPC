#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int p;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &p);
        for (int i = 0; i < p; i++){
            for (int j = 0; j < p; j++){
                if (j) putchar(' ');
                printf("%d", (i + j) % p);
            }
            puts("");
        }
        for (int i = 0; i < p; i++){
            for (int j = 0; j < p; j++){
                if (j) putchar(' ');
                printf("%d", 1ll * i * j % p);
            }
            puts("");
        }
    }
    return 0;
}