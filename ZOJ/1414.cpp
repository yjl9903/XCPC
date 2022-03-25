#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int x, y;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &x, &y);
        if (x == y){
            if (x % 4 == 0) printf("%d\n", 2 * x);
            else if (x % 4 == 1) printf("%d\n", 2 * x - 1);
            else if (x % 4 == 2) printf("%d\n", 2 * x);
            else printf("%d\n", 2 * x - 1);
        }
        else if (x == y + 2){
            if (y % 4 == 0) printf("%d\n", 2 * y + 2);
            else if (y % 4 == 1) printf("%d\n", 2 * y + 1);
            else if (y % 4 == 2) printf("%d\n", 2 * y + 2);
            else printf("%d\n", 2 * y + 1);
        }   
        else puts("No Number");
    }
    return 0;
}