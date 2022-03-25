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

bool check(int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        if (a[i] < a[i - 1]) return 0;
    }
    return 1;
}

int main() {
    cin >> n; for (int i = 1; i <= n; i++) cin >> a[i];
    int tot = n;
    while (tot) {
        for (int i = 1; i <= n; i += tot) {
            if (check(i, i + tot - 1)) {
                return printf("%d", tot), 0;
            }
        }
        tot /= 2;   
    }
    return 0;
}