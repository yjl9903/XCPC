#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <set>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m, a[5][300];

int max(int a, int b, int c) {
    return max(a, max(b, c));
}
int max(int a, int b, int c, int d) {
    return max(a, max(b, c, d));
}
int min(int a, int b, int c, int d) {
    return min(min(a, b), min(c, d));
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        int ans = 0;
        if (n == 1) {
            for (int i = 1; i <= m; i++) ans = max(ans, a[1][i]);
        } else if (n == 2) {
            vector<int> v;
            for (int i = 1; i <= m; i++) {
                ans = max(ans, a[1][i] + a[2][i]);
                v.push_back(max(a[1][i], a[2][i]));
            }
            if (m >= 2) {
                sort(v.begin(), v.end());
                reverse(v.begin(), v.end());
                ans = max(ans, v[0] + v[1]);
            }
        } else if (n == 3) {
            vector<int> v1;
            multiset<int> st;
            for (int i = 1; i <= m; i++) {
                ans = max(ans, a[1][i] + a[2][i] + a[3][i]);
                v1.push_back(max(a[1][i], a[2][i], a[3][i]));
                st.insert(max(a[1][i], a[2][i], a[3][i]));
            }
            sort(v1.begin(), v1.end());
            reverse(v1.begin(), v1.end());
            if (m >= 3) {
                ans = max(ans, v1[0] + v1[1] + v1[2]);
            }
            if (m >= 2) {
                for (int i = 1; i <= m; i++) {
                    st.erase(st.find(max(a[1][i], a[2][i], a[3][i])));
                    ans = max(ans, *st.rbegin() + max(a[1][i] + a[2][i], a[2][i] + a[3][i], a[3][i] + a[1][i]));
                    st.insert(max(a[1][i], a[2][i], a[3][i]));
                }
            }
        } else {
            vector<int> v1;
            multiset<int> st, st2, st3;
            for (int i = 1; i <= m; i++) {
                ans = max(ans, a[1][i] + a[2][i] + a[3][i] + a[4][i]);
                v1.push_back(max(a[1][i], a[2][i], a[3][i], a[4][i]));
                st.insert(max(a[1][i], a[2][i], a[3][i], a[4][i]));
                st2.insert(max(a[1][i] + a[3][i], a[2][i] + a[4][i]));
                st3.insert(max(a[1][i] + a[2][i], a[2][i] + a[3][i], a[3][i] + a[4][i], a[4][i] + a[1][i]));
            }
            sort(v1.begin(), v1.end());
            reverse(v1.begin(), v1.end());
            if (m >= 4) {
                ans = max(ans, v1[0] + v1[1] + v1[2] + v1[3]);
            }
            if (m >= 3) {
                for (int i = 1; i <= m; i++) {
                    st.erase(st.find(max(a[1][i], a[2][i], a[3][i], a[4][i])));
                    auto it = st.end(); it--;
                    int tot = *it; it--; tot += *it;
                    ans = max(ans, tot + max(a[1][i] + a[3][i], a[2][i] + a[4][i]));
                    ans = max(ans, tot + max(a[1][i] + a[2][i], a[2][i] + a[3][i], a[3][i] + a[4][i], a[4][i] + a[1][i]));
                    st.insert(max(a[1][i], a[2][i], a[3][i], a[4][i]));
                }
            }
            if (m >= 2) {
                for (int i = 1; i <= m; i++) {
                    st.erase(st.find(max(a[1][i], a[2][i], a[3][i], a[4][i])));
                    ans = max(ans, *st.rbegin() + a[1][i] + a[2][i] + a[3][i] + a[4][i] - min(a[1][i], a[2][i], a[3][i], a[4][i]));
                    st.insert(max(a[1][i], a[2][i], a[3][i], a[4][i]));
                }
                for (int i = 1; i <= m; i++) {
                    st2.erase(st2.find(max(a[1][i] + a[3][i], a[2][i] + a[4][i])));
                    ans = max(ans, *st2.rbegin() + max(a[1][i] + a[3][i], a[2][i] + a[4][i]));
                    st2.insert(max(a[1][i] + a[3][i], a[2][i] + a[4][i]));
                }
                for (int i = 1; i <= m; i++) {
                    st3.erase(st3.find(max(a[1][i] + a[2][i], a[2][i] + a[3][i], a[3][i] + a[4][i], a[4][i] + a[1][i])));
                    ans = max(ans, *st3.rbegin() + max(a[1][i] + a[2][i], a[2][i] + a[3][i], a[3][i] + a[4][i], a[4][i] + a[1][i]));
                    st3.insert(max(a[1][i] + a[2][i], a[2][i] + a[3][i], a[3][i] + a[4][i], a[4][i] + a[1][i]));
                }
            }
        }
        printf("%d\n", ans);
    }   
    return 0;
}