#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1000000 + 5;

int n, m, a[maxn];

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    sort(a + 1, a + 1 + n);
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] - a[i - 1] > m) ans++;
    }
    cout << ans << endl;
    return 0;
}