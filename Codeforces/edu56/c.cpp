#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n;
ll a[maxn], b[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n / 2; i++) scanf("%I64d", b + i);
    a[1] = 0; a[n] = b[1];
    for (int i = 2; i <= n / 2; i++) {
        if (b[i] - a[i - 1] <= a[n - i + 2]) {
            a[i] = a[i - 1]; a[n - i + 1] = b[i] - a[i - 1];
        } else {
            a[n - i + 1] = a[n - i + 2];
            a[i] = b[i] - a[n - i + 2];
        }
        assert(a[i] >= a[i - 1] && a[n - i + 2] >= a[n - i + 1]);
    }
    for (int i = 1; i <= n; i++) printf("%I64d ", a[i]);
    return 0;
}