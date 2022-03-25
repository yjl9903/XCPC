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
const int maxn = 200000 + 5;

int n;

bool isprime(int x) {
    int sq = (int)(sqrt(1.0 * x) + 0.5);
    for (int i = 2; i <= sq; i++) if (x % i == 0) return 0;
    return 1;
}

int main() {
    scanf("%d", &n);
    int x1 = 0, x2 = 0;
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        if (a == 1) x1++;
        else x2++;
    }
    int tot = 0;
    for (int i = 1; i <= n; i++) {
        if (x2 && isprime(tot + 2)) {
            printf("2 ");
            tot += 2; x2--;
        } else if (x1 && isprime(tot + 1)) {
            printf("1 ");
            tot += 1; x1--;
        } else if (x2) {
            printf("2 ");
            tot += 2; x2--;
        } else if (x1) {
            printf("1 ");
            tot += 1; x1--;
        }
    }
    return 0;
}