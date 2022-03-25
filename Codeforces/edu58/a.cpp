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

int l, r, d;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &l, &r, &d);
        if (l > d) printf("%d\n", d);
        else {
            int k = r / d + 1;
            printf("%I64d\n", 1ll * k * d); 
        }
    }
    return 0;
}