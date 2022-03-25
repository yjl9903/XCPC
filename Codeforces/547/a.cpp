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

int n, m;

int main() {
    cin >> n >> m;
    int k = m / n, ans = 0;
    if (m % n) return puts("-1"), 0;
    while (k % 2 == 0) {
        ans++; k /= 2;
    }
    while (k % 3 == 0) {
        ans++; k /= 3;
    }
    if (k != 1) puts("-1");
    else cout << ans << endl;
    return 0;
}