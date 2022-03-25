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

int n, a[maxn];

int main() {
    scanf("%d", &n); int sum = 0;
    for (int i = 0; i < n; i++) scanf("%d", a + i), sum += a[i];
    sort(a, a + n);
    int mn = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 2; j <= a[i]; j++) {
            if (a[i] % j) continue;
            mn = min(mn, (j - 1) * (a[0] - a[i] / j));
            // cout << (a[0] - a[i] / j) << endl;
        }

    }
    cout << sum + mn << endl;
    return 0;
}