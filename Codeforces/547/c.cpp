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
const int maxn = 200000 + 5;

int n, q[maxn], p[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) scanf("%d", q + i);
    set<int> st; st.insert(0);
    for (int i = 1; i < n; i++) {
        q[i] += q[i - 1];
        if (q[i] - *st.begin() >= n) return puts("-1"), 0;
        if (*st.rbegin() - q[i] >= n) return puts("-1"), 0;
        if (st.count(q[i])) return puts("-1"), 0;
        st.insert(q[i]);
        // mx = max(mx, q[i]);
        // mn = min(mn, q[i]);
    }
    int mn = *st.begin();
    printf("%d", -mn + 1);
    for (int i = 1; i < n; i++) printf(" %d", q[i] - mn + 1);
    return 0;
}