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

int n, m, x1, y_1, x2, y2;

int main() {
    cin >> n >> m >> x1 >> y_1 >> x2 >> y2;
    int d = abs(x1 - x2) + abs(y_1 - y2);
    // if (d == 1) puts("Lose");
    // if (d == 2) puts("Win");
    if (d % 2 == 0) puts("Win");
    else puts("Lose");
    return 0;
}