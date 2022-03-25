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
    if (z == 0 && x == y) puts("0");
    else {
        if (x + z < y) puts("-");
        else if (y + z < x) puts("+");
        else puts("?");
    }
    return 0;
}