#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <assert.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, a[maxn], b[maxn], c[maxn];
multiset<int> st;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", b + i), st.insert(b[i]);
    for (int i = 1; i <= n; i++) {
        multiset<int>::iterator it = st.begin();
        multiset<int>::iterator it2 = st.lower_bound(n - a[i]);
        if (it2 == st.end()) {
            if (it == st.end()) {
                printf("%d ", a[i] % n);
                continue;
            } else {
                printf("%d ", (a[i] + *it) % n);
                st.erase(it);
                continue;
            }
        }
        int x1 = (a[i] + *it) % n, x2 = (a[i] + *it2) % n;
        if (x1 < x2) {
            if (it == st.end()) {
                printf("%d ", a[i] % n);
                continue;
            }
            st.erase(it); printf("%d ", x1);
        } else {
            st.erase(it2); printf("%d ", x2);
        }
    }
    return 0;
}