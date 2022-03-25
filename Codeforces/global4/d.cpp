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

namespace sieve{
    const int maxp = 1000000 + 5;
    int vis[maxp], prime[maxp], tot;
    void init() {
        for (int i = 2; i < maxp; i++) {
            if (!vis[i]) prime[tot++] = i;
            for (int j = 0; j < tot && prime[j] * i < maxp; j++) {
                vis[i * prime[j]] = 1;
                if (i % prime[j] == 0) break;
            }
        }
    }
}
using namespace sieve;

int n, deg[maxn];

int check() {
    for (int i = 1; i <= n; i++) if (vis[deg[i]]) return true;
    return false;
}

int main() {
    init();
    cin >> n;
    vector<PII> ans; set<PII> st;
    ans.push_back({1, n}); st.insert({1, n});
    for (int i = 1; i < n; i++) ans.push_back({i, i + 1}), st.insert({i, i + 1});
    for (int i = 1; i <= n; i++) deg[i] = 2;
    while (vis[(int)ans.size()] || check()) {
        vector<int> v;
        for (int i = 1; i <= n; i++) {
            if (vis[deg[i]] || !vis[deg[i] + 1]) {
                if (deg[i] == n - 1) continue;
                if (!v.empty() && st.count({v[0], i})) continue;
                v.push_back(i); 
                if ((int)v.size() == 2) break;
            }
        }
        if ((int)v.size() == 2) {
            deg[v[0]]++; deg[v[1]]++;
            ans.push_back({v[0], v[1]});
            st.insert({v[0], v[1]});
            continue;
        }
        for (int i = 1; i <= n && (int)v.size() < 2; i++) {
            if (v.empty()) v.push_back(i);
            else if (i != v[0]) v.push_back(i);
        }
        deg[v[0]]++; deg[v[1]]++;
        ans.push_back({v[0], v[1]});
        if (v[0] > v[1]) swap(v[0], v[1]);
        st.insert({v[0], v[1]});
    }
    // for (int i = 1; i <= n; i++) cout << deg[i] << ' '; cout << endl;
    printf("%d\n", (int)ans.size());
    for (auto x: ans) printf("%d %d\n", x.first, x.second);
    return 0;
}