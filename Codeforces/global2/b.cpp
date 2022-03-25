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

int n, h, a[maxn];

ll cal(vector<int> v, int l, int r) {
    ll sum = 0;
    for (int i = l; i < r; i += 2) {
        sum += max(v[i], v[i + 1]);
    }
    return sum;
}
bool check(int m) {
    vector<int> v;
    for (int i = 1; i <= m; i++) v.push_back(a[i]);
    sort(v.begin(), v.end());
    if (m % 2 == 0) return cal(v, 0, m) <= h;
    return min(cal(v, 0, m - 1) + v[m - 1], cal(v, 1, m) + v[0]) <= h;
}

int main() {
    scanf("%d%d", &n, &h);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int ans = 0;
    for (int i = 1; i <= n; i++) if (check(i)) ans = i;
    cout << ans << endl;
    return 0;
}