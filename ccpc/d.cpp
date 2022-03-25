#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 40000 + 5;
const int inf = (int)1e9 + 2;

int n, a;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &a);
        if (n == 0 || n > 2){
            puts("-1 -1");
            continue;
        }
        if (n == 1){
            printf("%d %d\n", 1, a + 1);
            continue;
        }
        else if (n == 2){
            if (a % 2){
                int b = (a * a - 1) / 2;
                printf("%d %d\n", b, b + 1);
                continue;
            }
            if (a % 4 == 0){
                int b = a / 4;
                printf("%d %d\n", 3 * b, 5 * b);
                continue;
            }
            else if (a % 4 == 2){
                a /= 2;
                int b = (a * a - 1);
                printf("%d %d\n", b, b + 2);
            }
        }
    }
    return 0;
}