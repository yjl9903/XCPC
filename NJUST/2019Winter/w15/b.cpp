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

ll n, m;

int main() {
    cin >> n >> m;
    ll k = n / m, r = n % m;
    ll mn = 1ll * r * (k + 1) * (k + 1) + 1ll * (m - r) * k * k - n;
    ll mx = 1ll * (n - m + 1) * (n - m);
    cout << mn / 2 << ' ' << mx / 2 << endl;
    return 0;
}