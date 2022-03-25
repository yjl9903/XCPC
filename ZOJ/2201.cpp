#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a, b;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &a, &b);
        if (a >= b) puts("MMM BRAINS");
        else puts("NO BRAINS");
    }
    return 0;
}