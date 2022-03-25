#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll l, r;

int main(){
    scanf("%I64d%I64d", &l, &r);
    puts("YES");
    for (ll i = l; i < r; i += 2){
        printf("%I64d %I64d\n", i, i + 1);
    }
    return 0;
}