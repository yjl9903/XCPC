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

int n, a, b, x, y;

int check1(int p) {
    if (a < x) {
        if (a <= p && p <= x) return p - a;
        return -1;
    } else {
        if (p >= a) return p - a;
        else if (p <= x) return n - a + p;
        return -1;
    }
}
int check2(int p) {
    if (b > y) {
        if (b >= p && p >= y) return b - p;
        return -1;
    } else {
        if (p <= b) return b - p;
        else if (p >= y) return b + n - p;
        return -1;
    }
}

int main() {
    cin >> n >> a >> x >> b >> y;
    int f = 0;
    for (int i = 1; i <= n; i++) {
        int a = check1(i), b = check2(i);
        // cout << i << ": "<< a << ' ' << b << endl;
        if (a == -1 || b == -1) continue;
        if (a == b) f = 1;
    }
    if (f) puts("YES");
    else puts("NO");
    return 0;
}