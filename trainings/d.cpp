#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n, x1, y1, x2, y2;

int main(){
    cin >> n >> x1 >> y1 >> x2 >> y2;
    ll d = abs(x1 - x2) + abs(y1 - y2), k = 1;
    if (x1 == x2 && y1 == y2) k = 0;
    if (n < d) puts("0");
    else printf("%lld\n", (n - d) / 2 + k);
    return 0;
}