#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int x, y, z;

int main() {
    cin >> x >> y >> z;
    int f1 = 0, f2 = 0, f3 = 0;
    if (x + z > y) f1 = 1;
    if (y + z > x) f2 = 1;
    if (abs(x - y) <= z) f3 = 1;
    int sum = f1 + f2 + f3;
    if (sum > 1) puts("?");
    else if (f1) puts("+");
    else if (f2) puts("-");
    else puts("0");
    return 0;
}