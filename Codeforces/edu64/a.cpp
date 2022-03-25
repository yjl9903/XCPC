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

int n, a[maxn];

int main() {
    scanf("%d", &n);
    int ans = 0, flag = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (i > 1) {
            if (a[i] == 1) {
                if (a[i - 1] == 2) ans += 3;
                else if (a[i - 1] == 3) ans += 4;
            } else if (a[i] == 2) {
                if (a[i - 1] == 1) {
                    if (i > 2) {
                        if (a[i - 2] == 3) ans += 2;
                        else ans += 3;
                    } else {
                        ans += 3;
                    }
                } else if (a[i - 1] == 3) flag = 1;
            } else if (a[i] == 3) {
                if (a[i - 1] == 1) ans += 4;
                else if (a[i - 1] == 2) flag = 1;
            }
        }
    }
    if (flag) return puts("Infinite"), 0;
    puts("Finite");
    cout << ans;
    return 0;
}