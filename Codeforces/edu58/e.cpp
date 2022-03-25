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

char op[2]; int x, y, mx, my;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s%d%d", op, &x, &y);
        if (op[0] == '+') {
            if (x > y) swap(x, y);
            mx = max(mx, x); my = max(my, y);
        }
        if (op[0] == '?') {
            if (x >= mx && y >= my) puts("YES");
            else if (x >= my && y >= mx) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}