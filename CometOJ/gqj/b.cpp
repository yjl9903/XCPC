#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int a[10];

int main() {
    ll sum = 0, ans = 0;
    for (int i = 1; i <= 5; i++) scanf("%d", a + i), sum += a[i];
    sort(a + 1, a + 6);
    if (a[5] >= sum - a[5]) cout << a[5];
    else cout << sum / 2;
    return 0;
}