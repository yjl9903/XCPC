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
const int maxn = 300000 + 5;

int n, c[maxn], loc[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", c + i);
    set<PII> st; st.insert({1, c[1]});
    loc[c[1]] = 1;
    int ans = 0;
    for (int i = 2; i <= n; i++) {
        auto it = st.begin();
        if ((*it).second == c[i]) it++;
        if (it == st.end()) continue;
        ans = max(ans, i - (*it).first);
        if (!loc[c[i]]) {
            loc[c[i]] = i; st.insert({i, c[i]});
        }
    }
    cout << ans << endl;
    return 0;
}