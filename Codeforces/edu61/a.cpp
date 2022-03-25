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

int c1, c2, c3, c4;

int main() {
    cin >> c1 >> c2 >> c3 >> c4;
    if (c1 == c4) {
        if (c1 == 0) {
            if (c3) puts("0");
            else puts("1");
        } else puts("1");
    } else puts("0");
    return 0;
}