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

int h, m;

int main() {
    scanf("%d:%d", &h, &m);
    if (h >= 0 && h < 12) {
        printf("Only %02d:%02d.  Too early to Dang.", h, m);
    } else if (h == 12 && m == 0) {
        printf("Only %02d:%02d.  Too early to Dang.", h, m);
    } else {
        int cnt = h - 12;
        if (m) cnt++;
        while (cnt--) printf("Dang");
    }
    return 0;
}