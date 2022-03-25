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

int n, k, a[maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    vector<int> v;
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
        v.push_back(a[i] + a[j]);
    }
    sort(v.begin(), v.end()); reverse(v.begin(), v.end());
    ll ans = 0;
    for (int i = 0; i < k; i++) ans += v[i];
    cout << ans;
    return 0;
}