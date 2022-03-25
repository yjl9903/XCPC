#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, a, b[3];

int main() {
    cin >> n >> a;
    // double x = 1.0 * n * a / 180.0;
    // b[0] = (int)x - 1;
    // b[1] = (int)x;
    // b[2] = (int)x + 1;
    int ans = -1, m = 1e9;
    // for (int i = 0; i < 3; i++) {
    //     if (b[i] < 1 || b[i] > n - 1) continue;
    //     int ang = 180 * b[i];
    //     if (abs(ang - n * a) < m) {
    //         m = abs(ang - n * a); ans = b[i];
    //     }
    // }
    for (int i = 1; i < n - 1; i++) {
        int ang = 180 * i;
        if (abs(ang - n * a) < m) {
            m = abs(ang - n * a); ans = i;
        }
    }
    cout << "1 " << n << " " << ans + 1 << endl;
    return 0;
}