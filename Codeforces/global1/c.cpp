#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int a, b[30];
int ans[] = { 0,0,1,1,5,1,21,1,85,73,341,89,1365,1,5461,4681,21845,1,87381,1,349525,299593,1398101,178481,5592405,1082401 };

int cal(int x) {
    int ans = 0;
    for (int i = 1; i < x; i++) ans = max(ans, __gcd(i, x - i));
    return ans;
}

int main() {
    for (int i = 1; i < 26; i++) b[i] = (1 << i) - 1;
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &a);
        int ans = 0, k = 0;
        for (int i = 1; i < 26; i++) if (a & (1 << i)) k = i + 1;
        ans = (1 << k) - 1;
        for (int i = 1; i < 26; i++) if (a == b[i]) {
            ans = ::ans[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}