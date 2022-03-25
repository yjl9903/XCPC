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

char g1(int x, int y, int z) {
    if (z == 0 && x == y) return '0';
    else {
        if (x + z < y) return '-';
        else if (y + z < x) return '+';
        else return '?';
    }
}
char g2(int x, int y, int z) {
    int f1 = 0, f2 = 0, f3 = 0;
    if (x + z > y) f1 = 1;
    if (y + z > x) f2 = 1;
    if (abs(x - y) <= z) f3 = 1;
    int sum = f1 + f2 + f3;
    if (sum > 1) return '?';
    else if (f1) return '+';
    else if (f2) return '-';
    else return '0';
}

int main() {
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            for (int k = 0; k <= 100; k++) {
                char r1 = g1(i, j, k);
                char r2 = g2(i, j, k);
                // cout << r1 << ' ' << r2 << endl;
                if (r1 == r2) {

                } else {
                    cout << i << ' ' << j << ' ' << k << endl;
                }
            }
        }
    }
    return 0;
}