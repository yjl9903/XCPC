#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = (int)1e8 + 5;

int a[maxn], n, m;

int main(){
    a[0] = 0; a[1] = 2;
    for (int i = 2; i < maxn; i++) a[i] = (3 * a[i - 1] - a[i - 2]) / 2 + i + 1;
    while (~scanf("%d%d", &n, &m)){

    }
    return 0;
}