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

void exgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) x = 1, y = 0;
    else {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}
void exgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) x = 1, y = 0
    else {
        exgcd(b, a % b, y, x)
        y -= a / b * x
    }
}

int main() {
    ll a, b, x, y;
    cin >> a >> b;
    exgcd(a, b, x, y);
    // cout << x << ' ' << y << endl;
    cout << (x + b) % b;
    return 0;
}