#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int b, g, n;

int main() {
    cin >> b >> g >> n;
    if (b >= n && g >= n) cout << n + 1;
    else if (b >= n) cout << g + 1;
    else if (g >= n) cout << b + 1;
    else cout << b - n + g + 1;
    return 0;
}