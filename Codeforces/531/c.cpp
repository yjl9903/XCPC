#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, x, y, a[maxn];
multiset<int> st;

int main(){
    scanf("%d%d%d", &n, &x, &y);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    if (x > y) return printf("%d", n), 0;
    int ans = 1;
    for (int i = 1; i <= n; i++) if (a[i] <= x) ans++;
    cout << ans / 2;
    // int ans = 0;
    // while (true) {
    //     auto r = st.upper_bound(x);
    //     if (r == st.begin()) break;
    //     r--; ans++;
    //     st.erase(r);
    //     st.erase(*st.begin());
    // }
    // cout << ans;
    return 0;
}