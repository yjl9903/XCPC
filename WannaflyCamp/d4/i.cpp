#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, k;
PII a[maxn];
ll sum;

bool cmp(PII a, PII b) {
    ll x = 1ll * k * a.second - a.first, y = 1ll * k * b.second - b.first;
    return x > y;
}
ll cal(int x) {
    k = x;
    nth_element(a, a + n - x, a + n, cmp);
    ll s = 0;
    for (int i = 0; i < n - x; i++) s += 1ll * k * a[i].second - a[i].first;
    return s + sum;
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", &a[i].first, &a[i].second), sum += a[i].first;
    int l = 0, r = n;
    while (l + 2 < r) {
        int ml = (2 * l + r) / 3, mr = (l + 2 * r) / 3;
        ll s1 = cal(ml), s2 = cal(mr);
        if (s1 < s2) l = ml;
        else r = mr;
    }
    cout << max(max(cal(l), cal(r)), max(cal((2 * r + l) / 3), cal((2 * l + r) / 3))) << endl;
    return 0;
}