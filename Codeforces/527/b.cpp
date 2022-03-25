#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, a[maxn];

int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    sort(a + 1, a + n + 1);
    int ans = 0;
    for (int i = 2; i <= n; i += 2) {
        ans += a[i] - a[i - 1];
    }
    cout << ans;
    return 0;
}