#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int x, y, z, a, b, c;

int main() {
    cin >> x >> y >> z >> a >> b >> c;
    if (x > a) return puts("NO"), 0;
    a -= x;
    if (y > a + b) return puts("NO"), 0;
    if (z > a + b - y + c) return puts("NO"), 0;
    puts("YES");
    return 0;
}