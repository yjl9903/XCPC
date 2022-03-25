#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int x1, y1, x2, y2, x, y;

int main(){
    cin >> x1 >> y1 >> x2 >> y2 >> x >> y;
    int dx = abs(x1 - x2), dy = abs(y1 - y2);
    if (dx % x == 0 && dy % y == 0 && dx / x % 2 == dy / y % 2) puts("YES");
    else puts("NO");
    return 0;
}