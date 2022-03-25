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

ll n, a, b, p, q;

int main() {
    cin >> n >> a >> b >> p >> q;
    ll x = n / a * p;
    ll y = n / b * q;
    ll z = n / (a * b) * min(p, q);
    cout << x + y - z << endl;
    return 0;
}