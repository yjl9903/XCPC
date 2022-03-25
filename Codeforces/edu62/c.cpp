#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, k;
PII a[maxn];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    sort(a + 1, a + 1 + n, [](PII a, PII b) {
        if (a.second == b.second) return a.first > b.first;
        return a.second < b.second;
    });
    ll ans = 0, sum = 0; 
    multiset<ll> st;
    for (int i = n; i >= 1; i--) {
        if ((int)st.size() == k) {
            if (a[i].first > *st.begin()) {
                sum -= *st.begin();
                st.erase(st.begin());
                sum += a[i].first;
                st.insert(a[i].first);
            }
        } else {
            st.insert(a[i].first);
            sum += a[i].first;
        }
        ans = max(ans, sum * a[i].second);
    }
    cout << ans << endl;
    return 0;
}