#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, a[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int ans = inf;
    for (int l = 0; l <= n; l++) {
        set<int> st;
        int flag = 0;
        for (int i = 1; i <= l; i++) {
            if (st.count(a[i])) {
                flag = 1; break;
            }
            st.insert(a[i]);
        }
        if (flag) break;
        ans = min(ans, n - l);
        for (int r = n; r > l; r--) {
            if (st.count(a[r])) break;
            st.insert(a[r]);
            ans = min(ans, r - l - 1);
        }
    }
    printf("%d\n", ans);
    return 0;
}