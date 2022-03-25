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

ll x, y, z;

int main() {
    cin >> x >> y >> z;
    ll a = x / z + y / z;
    ll a1 = x / z + (y + x % z) / z;
    ll a2 = y / z + (x + y % z) / z;
    ll r1 = z - y % z; if (r1 == z) r1 = 0;
    ll r2 = z - x % z; if (r2 == z) r2 = 0;
    if (a == a1) r1 = 0;
    if (a == a2) r2 = 0;
    if (a1 >= a2 && r1 < r2) {
        cout << a1 << ' ';
        cout << r1;
    } else {
        cout << a2 << ' ';
        cout << r2;
    }
    return 0;
}