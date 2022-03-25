#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 500000 + 5;

int n, a[maxn], cnt[maxn];
vector<int> v;

int check(int m) {  
    for (int i = 0; i <= n; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++) cnt[a[i]]++;
    cnt[m]++;
    ll s = 0, r = 0, ls = 0;
    for (int i = 0, j = 0; i <= n; i++) {
        int val = (i == j && (i == n || a[j] < m)) ? m : a[j++];
        s += val;
        cnt[val]--;
        r -= min(i, a[i]);
        ls += cnt[i];
        r += n - i - ls;
        if (s > r + 1ll * i * (i + 1)) {
            if (i == j) return 1;
            else return -1;
        }
    }
    return 0;
}

int main(){
    scanf("%d", &n); ll sum = 0;
    for (int i = 0; i < n; i++) scanf("%d", a + i), sum += a[i];
    sort(a, a + n, [](int x, int y){return x > y;});
    int l = 0, r = (n - sum % 2) / 2, u = -1, d = -1;
    while (l <= r) {
        int m = l + r >> 1;
        if (check(2 * m + sum % 2) == -1) l = m + 1; // m small
        else r = m - 1, d = m; 
    }
    l = d, r = (n - sum % 2) / 2;
    while (l <= r) {
        int m = l + r >> 1;
        if (check(2 * m + sum % 2) == 1) r = m - 1; // m big
        else l = m + 1, u = m;
    }
    // cout << d << ' ' << u << endl;
    if (u == -1 || d == -1) puts("-1");
    else {
        for (int i = d; i <= u; i++) printf("%d ", 2 * i + sum % 2);
    }
    return 0;
}