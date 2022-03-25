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

int n, a[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    int f = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] > a[i - 1]) {
            if (f == 0) return puts("NO"), 0;
        } else if (a[i] == a[i - 1]) return puts("NO"), 0;
        else {
            if (f) f = 0;
        }
    }
    puts("YES");
    return 0;
}