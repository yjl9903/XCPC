#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int x, y, z, t1, t2, t3;

int main(){
    cin >> x >> y >> z >> t1 >> t2 >> t3;
    ll a = 1ll * abs(x - y) * t1;
    ll b = 1ll * abs(x - z) * t2 + 1ll * abs(x - y) * t2 + 3ll * t3;
    // cout << a << ' ' << b << endl;
    if (a >= b) puts("YES");
    else puts("NO");
    return 0;
}