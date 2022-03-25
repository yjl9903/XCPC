#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 200000 + 5;

int n;
ll a[maxn];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%I64d", a + i); 
    if (n == 2) {
        if ((a[2] - a[1]) % 2) puts("NO");
        else puts("YES");
        return 0;
    }
    ll last = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] < last) {
            a[i] += (last - a[i]) / 2 * 2;
            if (a[i] < last) a[i] += 2;
        }
        if (a[i] == last) continue;
        if ((a[i] - last) % 2 == 0 || (i - 1) % 2 == 0) {
            last = a[i]; continue;
        }
        if (a[i + 1] < a[i]) {
            a[i + 1] += (a[i] - a[i + 1]) / 2 * 2;
            if (a[i + 1] < a[i]) a[i + 1] += 2;
        }
        if (a[i + 1] == a[i]) {
            last = a[i + 1]; i++; continue;
        }
        
    }
    return 0;
}