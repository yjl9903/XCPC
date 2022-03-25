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

int n;

int main() {
    while (scanf("%d", &n) == 1) {
        int ans = 0;
        for (int i = 1, x; i <= n; i++) scanf("%d", &x), ans ^= x;
        if (ans) puts("Yes");
        else puts("No");
    }
    return 0;
}