#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 500000 + 5;

vector<int> lsh;
int n, k, a[maxn], cnt[maxn], bag[maxn], mx;

void update(int x, int k) {
    bag[cnt[x]]--; cnt[x] += k; bag[cnt[x]]++;
    if (cnt[x] > mx) mx = cnt[x];
    if (bag[mx] == 0) mx--;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), lsh.push_back(a[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    for (int i = 1; i <= n; i++) a[i] = lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1;
    int r = 0; ll ans = 0;
    for (int i = 1; i <= n; i++) {
        while (mx < k && r <= n) {
            update(a[++r], 1);
        }
        ans += n - r + 1;
        update(a[i], -1);
    }
    cout << ans << endl;
    return 0;
}