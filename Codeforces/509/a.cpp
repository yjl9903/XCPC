#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[maxn];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    int k = a[n - 1] - a[0];
    printf("%d", k + 1 - n);
    return 0;
}