#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a[5];

int main(){
    while (~scanf("%d%d%d", a, a + 1, a + 2)){
        sort(a, a + 3);
        if (a[0] <= 168) {
            printf("CRASH %d\n", a[0]); continue;
        }
        if (a[1] <= 168){
            printf("CRASH %d\n", a[1]); continue;
        }
        if (a[2] <= 168){
            printf("CRASH %d\n", a[2]); continue;
        }
        puts("NO CRASH");
    }
    return 0;
}