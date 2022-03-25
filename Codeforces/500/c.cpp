#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long LL;
const int maxn = 100000 + 5;

int n, a[2 * maxn];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; i++) scanf("%d", &a[i]);
    sort(a, a + 2 * n);
    int x1 = a[0], y1 = a[n], x2 = a[n - 1], y2 = a[2 * n - 1];
    LL s = 1ull * (x2 - x1) * (y2 - y1);
    for (int i = 1; i <= n; i++) s = min(1ull * (y2 - x1) * (a[i + n - 1] - a[i]), s);
    cout << s;
    return 0;
}