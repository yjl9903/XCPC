#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, h[maxn], l[maxn], r[maxn];

int main() {
    while (scanf("%d", &n) && n) {
        ms(r, 0); ms(l, 0);
        vector<int> st;
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", h + i);
            while (!st.empty() && h[st.back()] > h[i]) {
                r[st.back()] = i - 1;
                st.pop_back();
            }
            st.push_back(i);
        }
        st.clear();
        for (int i = n; i >= 1; i--) {
            while (!st.empty() && h[st.back()] > h[i]) {
                l[st.back()] = i + 1; st.pop_back();
            }
            st.push_back(i);
        }
        for (int i = 1; i <= n; i++) {
            if (!r[i]) r[i] = n;
            if (!l[i]) l[i] = 1;
        }
        for (int i = 1; i <= n; i++) {
            ans = max(ans, 1ll * h[i] * (r[i] - l[i] + 1));
        }
        printf("%lld\n", ans);
    }
    return 0;
}