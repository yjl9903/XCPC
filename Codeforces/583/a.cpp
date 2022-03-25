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

int n, e, d;

int main() {
    cin >> n >> e >> d;
    d *= 5;
    int ans = 0;
    for (int i = 0; i * d <= n; i++) ans = max(ans, i * d + (n - i * d) / e * e);
    cout << n - ans;
    return 0;
}