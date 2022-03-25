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
const int maxn = 200000 + 5;

int n, a[maxn];

int main() {
    cin >> n;
    if (n % 2 == 0) return puts("NO"), 0;
    puts("YES");
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            a[i] = 2 * i - 1;
            a[i + n] = 2 * i;
        } else {
            a[i] = 2 * i;
            a[i + n] = 2 * i - 1;
        }
    }
    for (int i = 1; i <= 2 * n; i++) printf("%d ", a[i]);
    return 0;
}