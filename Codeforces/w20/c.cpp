#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, m;
set<int> d1, d2;

int main() {
    scanf("%d%d", &n, &m);
    if (m == 0) return printf("%d\n", n - 1), 0;
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        if (u > v) swap(u, v);
        d2.insert(u); d1.insert(v);
    }
    if (*d2.rbegin() >= *d1.begin()) return puts("0"), 0;
    printf("%d\n", *d1.begin() - *d2.rbegin());
    return 0;
}