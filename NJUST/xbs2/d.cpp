#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, a[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        map<int,int> mp;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            if (a[i] < 0) mp[a[i]]++;
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) if (a[i] > 0) {
            ans += mp[-a[i]];
        }
        printf("%d\n", ans);
    }
    return 0;
}