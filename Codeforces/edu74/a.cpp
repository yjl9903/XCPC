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

ll a, b;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> a >> b;
        if (abs(a - b) == 1) puts("No");
        else puts("Yes");
    }
    return 0;
}