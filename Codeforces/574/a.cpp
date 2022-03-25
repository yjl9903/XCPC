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

int n, k, a[maxn], cnt[maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), cnt[a[i]]++;
    int odd = 0, used = 0;
    for (int i = 1; i <= k; i++) {
        used += cnt[i] / 2;
        odd += cnt[i] % 2;
    }
    int all = n / 2 + n % 2;
    cout << used * 2 + min(odd, all - used);
    return 0;
}