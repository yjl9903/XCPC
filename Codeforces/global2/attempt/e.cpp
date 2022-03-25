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
const int maxn = 300000 + 5;

int n, a[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    ll ans = 0;
    for (int i = 0; i < n; i++) ans += a[i] / 6 * 2, a[i] %= 6;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        
    }
    cout << ans << endl;
    return 0;
}