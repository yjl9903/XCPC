#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[maxn], b[maxn];

int main(){
    scanf("%d", &n);
    int s1 = 0, s2 = 0, s = n * (n + 1) / 2;
    for (int i = 0; i < n; i++) scanf("%d", &a[i]), s1 += a[i];
    for (int i = 0; i < n; i++) scanf("%d", &b[i]), s2 += b[i];
    int res = 1;
    // if (s1 > s) res = 0;
    if (s2 > s1) res = 0;
    if (res) puts("Yes");
    else puts("No");
    return 0;
}