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

int w1, h1, w2, h2;

int main() {
    cin >> w1 >> h1 >> w2 >> h2;
    ll ans = (h1 + h2 + 2) * 2ll;
    ans += w1 + w2 + abs(w1 - w2);
    cout << ans << endl;
    return 0;
}