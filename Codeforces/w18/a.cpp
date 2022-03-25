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
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int ans = 1, i = 1;
    while (i <= n) {
        int j = i + 1;
        while (j <= n && a[j] >= a[j - 1]) j++;
        ans = max(ans, j - i);
        i = j;
    }
    cout << ans << endl;
    return 0;
}