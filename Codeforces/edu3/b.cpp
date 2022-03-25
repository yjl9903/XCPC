#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, m, a[maxn];

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    while (m--){
        int x; scanf("%d", &x);
        int r = upper_bound(a, a + n, x) - a;
        printf("%d ", r);
    }
    return 0;
}