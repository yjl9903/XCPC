#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, x[maxn], y[maxn], a[maxn], b[maxn];

int main(){
    scanf("%d", &n); 
    ll sumx = 0, sumy = 0;
    for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i), sumx += x[i], sumy += y[i];
    for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i), sumx += a[i], sumy += b[i];
    cout << sumx / n << ' ' << sumy / n;
    return 0;
}