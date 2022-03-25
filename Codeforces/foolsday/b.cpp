#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdlib>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;

int main() {
    cin >> n;
    switch (n) {
        case 2:
        case 3:
        case 4:
        case 5:
        case 12:
        case 30:
        case 35:
        case 43:
        case 46:
        case 52:
        case 64:
        case 86:
            puts("YES"); break;
        default:
            puts("NO");
    }
    // int cnt = 0;
    // while (n) {
    //     cnt += n % 10; n /= 10;
    // }
    // if (cnt % 5 == 0) puts("YES");
    // else puts("NO");
    return 0;
}