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

ll k2, k3, k5, k6;

int main() {
    cin >> k2 >> k3 >> k5 >> k6;
    ll a = min(k2, min(k5, k6)) * 256ll;
    k2 -= min(k2, min(k5, k6));
    cout << a + 32ll * min(k2, k3) << endl;
    return 0;
}