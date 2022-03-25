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
const int maxn = 200000 + 5;

int n, q, a[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    scanf("%d", &q);
    int op, p, x, tag = -1;
    set<PII> st;
    while (q--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &p, &x);
            if (st.count({ a[p], p })) st.erase({ a[p], p });
            a[p] = x;
            st.insert({ x, p });
        } else if (op == 2) {
            scanf("%d", &x);
            if (x > tag) {
                tag = x;
            }
            // st.clear();
            for (auto it = st.begin(); it != st.end();) {
                if (it->first >= x) break;
                auto it2 = it; it++;
                st.erase(it2);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (st.count({ a[i], i })) printf("%d ", a[i]);
        else printf("%d ", max(tag, a[i]));
    }
    return 0;
}