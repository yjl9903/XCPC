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

char s[maxn];
int n;

int main() {
    cin >> n;
    cin >> s + 1;
    ll ans = 0;
    for (int i = 1; i <= n; i++) if ((s[i] - '0') % 2 == 0) {
        ans += i;
    }
    cout << ans << endl;
    return 0;
}