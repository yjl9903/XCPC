#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, k, l[maxn], r[maxn];
vector<int> tin[maxn], tout[maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", l + i, r + i);
        tin[l[i]].push_back(i);
        tout[r[i] + 1].push_back(i);
    }
    vector<int> ans;
    set<PII> st;
    for (int i = 1; i < maxn; i++) {
        for (auto& x: tin[i]) {
            st.insert({r[x], x});
        }
        for (auto& x: tout[i]) {
            if (st.count({r[x], x})) st.erase({r[x], x});
        }
        while ((int)st.size() > k) {
            auto it = --st.end();
            ans.push_back(it->second);
            st.erase(it);
        }
    }
    printf("%d\n", (int)ans.size());
    for (int x: ans) printf("%d ", x);
    return 0;
}