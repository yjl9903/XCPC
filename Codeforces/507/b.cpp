#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, k;

int main(){
    scanf("%d%d", &n, &k);
    if (2 * k + 1 >= n){
        printf("1\n%d", n / 2 + 1);
        return 0;
    }
    if (n % (2 * k + 1) == 0){
        printf("%d\n", n / (2 * k + 1));
        for (int i = k + 1; i <= n; i += 2 * k + 1){
            printf("%d ", i);
        }
        return 0;
    }
    // int c = n % (2 * k + 1) + 2 * k + 1;
    printf("%d\n", n / (2 * k + 1) + 1);
    int sta = 1;
    if (n % (2 * k + 1) > k) sta = n % (2 * k + 1) - k;
    for (int i = sta; i <= n; i += 2 * k + 1){
        printf("%d ", i);
    }
    return 0;
}