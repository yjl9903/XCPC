#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a;

int main(){
    while (~scanf("%d%d", &n, &a)){
        printf("%d\n", (n + a) / 2);
    }
    return 0;
}