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
    ll sum = 0, mx = 0;
    for (int i = 1; i <= n; i++) scanf("%I64d", a + i);
    int i = 1, last = 0;
    while (i <= n) {
        ll sum = 0, mx = 0;
        int j = i;
        while (j <= n) {
            sum += a[j]; mx = max(a[i], mx);
            ll c = (j - last) * mx - sum, c2 = c + j - last;
            if (c % 2 && c2 % 2) {
                last = j - 1;
                i = j;
            }
            j++;
        }
        if (i == n) return puts("NO"), 0;
    }
    puts("YES");
    return 0;
}