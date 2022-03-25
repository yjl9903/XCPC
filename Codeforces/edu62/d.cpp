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

int n;

int main() {
    cin >> n;
    ll ans = 0;
    for (int i = 3; i <= n; i++) ans += 1ll * i * (i - 1); 
    cout << ans << endl;
    return 0;
}