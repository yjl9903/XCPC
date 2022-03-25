#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;

int main(){
    while (~scanf("%d", &n) && n){
        int x, last = 0;
        ll res = 0;
        while (n--){
            scanf("%d", &x);
            res += abs(last);
            last += x;
        }
        printf("%lld\n", res);
    }
    return 0;
}