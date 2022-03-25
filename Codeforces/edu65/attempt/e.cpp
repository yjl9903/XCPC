#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, x, a[maxn], first[maxn], last[maxn];
int mark[maxn], mn[maxn];

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (first[a[i]] == 0) first[a[i]] = i;
        last[a[i]] = i;
    }
    set<int> st;
    for (int i = 1; i <= n; i++) {
        auto it = st.upper_bound(a[i]);
        if (it == st.end()) {

        } else {
            mark[a[i]] = 1;
        }
        st.insert(a[i]);
    }
    st.clear(); st.insert(a[n]);
    for (int i = n - 1; i >= 1; i--) {
        mn[a[i]] = min(mn[a[i]], *st.begin());
        st.insert(a[i]);
    }
    ll ans = 0;
    for (int i = 0; i <= x; i++) {
        if (mark[i]) break;
        
    }
    cout << ans << endl;
    return 0;
}