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
const int maxn = 100000 + 5;

int n;
set<int> st;

int main() {
    scanf("%d", &n);
    int la = 0, lb = 0;
    scanf("%d%d", &la, &lb);
    int ans = min(la, lb) + 1;
    st.insert(min(la, lb));
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d%d", &a, &b);
        ans += max(0, min(a, b) - max(la, lb));
        if (a >= max(la, lb) && b >= max(la, lb) && !st.count(max(la, lb))) ans++;
        st.insert(min(a, b));
        la = a; lb = b;
    }
    cout << ans << endl;
    return 0;
}