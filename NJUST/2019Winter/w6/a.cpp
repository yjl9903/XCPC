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

int n, m, a[maxn];

int main(){
    scanf("%d%d", &n, &m);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int mn = 1e9 + 5;
        for (int j = 0; j < m; j++) {
            scanf("%d", a + j);
            mn = min(a[j], mn);
        }
        ans = max(mn, ans);
    }
    cout << ans << endl;
    return 0;
}