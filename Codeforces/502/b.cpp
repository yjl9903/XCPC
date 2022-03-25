#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n;
char a[maxn], b[maxn];

int main(){
    scanf("%d%s%s", &n, a, b);
    ll s[2] = {0, 0}, res = 0;
    for (int i = 0; i < n; i++) s[a[i] - '0']++;
    for (int i = 0; i < n; i++){
        if (b[i] == '1') continue;
        if (a[i] == '0') res += s[1], s[0]--;
        else if (a[i] == '1') res += s[0], s[1]--;
    }
    printf("%I64d\n", res);
    return 0;
}