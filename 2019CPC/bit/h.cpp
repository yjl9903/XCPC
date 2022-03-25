#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int a, b;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &a, &b);
        int d = (int)sqrt(4 * a * b + a * a);
        vector<int> v, ans;
        v.push_back((2 * b + a - d) / 2);
        v.push_back((2 * b + a + d) / 2);
        if (v[0] == v[1]) v.pop_back();
        for (int& x: v) {
            if (x >= b && a * x >= 0) ans.push_back(x);
        }
        if ((int)ans.size() == 1) {
            puts("1");
            printf("%d\n", ans[0]);
        } else if ((int)ans.size() == 2) {
            puts("2");
            printf("%d %d\n", ans[0], ans[1]);
        } else {
            assert(0);
        }
    }
    return 0;
}