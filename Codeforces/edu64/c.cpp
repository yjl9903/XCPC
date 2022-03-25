#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <queue>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, z, a[maxn];
multiset<int> st;

struct node {
    int val, tag;
    bool operator<(const node& b) const {
        return val > b.val;
    }
};

int main() {
    scanf("%d%d", &n, &z);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    sort(a + 1, a + 1 + n);
    int ans = 0;
    for (int i = n / 2 + 1; i <= n; i++) st.insert(a[i]);
    for (int i = 1; i <= n / 2; i++) {
        auto it = st.lower_bound(a[i] + z);
        if (it == st.end()) continue;
        st.erase(it); ans++;
    }
    cout << ans << endl;
    return 0;
}