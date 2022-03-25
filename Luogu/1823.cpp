#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, a[maxn], r[maxn], l[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    vector<int> st; st.push_back(1);
    ll ans = 0;
    for (int i = 2; i <= n; i++) {
        int l = 0, r = (int)st.size() - 1, res = 0;
        while (l <= r) {
            int m = (l + r) / 2;
            if (a[st[m]] > a[i]) res = m, l = m + 1;
            else r = m - 1;
        }
        ans += (int)st.size() - res;
        while (!st.empty() && a[i] > a[st.back()]) {
            st.pop_back();
        }
        st.push_back(i);
    }
    cout << ans;
    return 0;
}
/*
7
2 4 1 2 2 5 1
2
4 +1
4 1 +1
4 2 +2
4 2 +2
5 +3
5 1 +1
*/