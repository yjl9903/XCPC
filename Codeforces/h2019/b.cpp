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

int dfs(int p, int t) {
    if (p > n) return t % 360 == 0;
    if (dfs(p + 1, t + a[p])) return 1;
    if (dfs(p + 1, t - a[p])) return 1;
    return 0;
}

int main(){
    cin >> n; for (int i = 1; i <= n; i++) cin >> a[i];
    if (dfs(1, 0)) puts("YES");
    else puts("NO");
    return 0;
}