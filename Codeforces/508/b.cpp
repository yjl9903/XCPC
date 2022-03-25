#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 45000 + 5;

int n;

int main(){
    scanf("%d", &n);
    if (n == 1 || n == 2){
        puts("No"); return 0;
    }
    puts("Yes");
    printf("%d", n / 2);
    for (int i = 2; i <= n; i += 2) printf(" %d", i);
    printf("\n%d", n - n / 2);
    for (int i = 1; i <= n; i += 2) printf(" %d", i);
    return 0;
}