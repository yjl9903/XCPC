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

int n, a[maxn];

int main() {
    scanf("%d", &n);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        sum += a[i];
    }
    // if (a[1] >= sum / 2) return puts("1"), 0;
    vector<int> ans; ans.push_back(1);
    int tot = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[1] >= 2 * a[i]) {
            tot += a[i]; ans.push_back(i);
        }
    }
    if (tot < sum / 2 + 1) puts("0");
    else {
        cout << ans.size() << '\n';
        for (int x: ans) printf("%d ", x);
    }
    return 0;
}