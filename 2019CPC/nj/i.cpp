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
const int maxn = 1000000 + 5;

int n, y, a[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &y);
        int mx = 0;
        for (int i = 1; i <= n; i++) scanf("%d", a + i), mx = max(mx, a[i]);
        for (int i = y; i >= 1; i--) {
            
        }
    }
    return 0;
}