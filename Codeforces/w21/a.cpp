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
const int maxn = 100000 + 5;

int n; char tmp[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 0, x, y; i < n; i++) {
        scanf("%s%d%d", tmp, &x, &y);
        if (x >= 2400 & y > x) return puts("YES"), 0;
    }
    puts("NO");
    return 0;
}