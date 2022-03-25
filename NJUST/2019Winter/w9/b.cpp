#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<double, int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, m, ans[maxn], bag[maxn];
set<pair<int,PII> > st;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) st.insert({0, make_pair(abs((double)(m + 1) / 2.0 - i), i)});
    for (int i = 1; i <= n; i++) {
        auto tot = st.begin();
        ans[i] = tot->second.second;
        bag[ans[i]]++;
        st.erase(st.begin());
        st.insert({bag[ans[i]], make_pair(abs((double)(m + 1) / 2.0 - ans[i]), ans[i])});
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}