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

int n;
set<int> st;

int main() {
    cin >> n;
    for (int i = 2; i <= 3 * n + 1; i++) st.insert(i);
    vector<int> a, b, c;
    for (int i = 1; i <= n; i++) {
        int z = *st.rbegin(); st.erase(z);
        int x = *st.begin(); st.erase(x);
        int y = (int)sqrt(1ll * z * z - 1ll * x * x);
        auto it = st.upper_bound(y);
        if (it == st.begin()) break;
        it--;
        y = *it; st.erase(it);
        a.push_back(x); b.push_back(y); c.push_back(z);
    }
    if ((int)a.size() < n) return puts("-1"), 0;
    for (int i = 0; i < n; i++) printf("%d %d %d\n", a[i], b[i], c[i]);
    return 0;
}