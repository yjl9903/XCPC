#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
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
const int maxn = 200000 + 5;

int n, tot = 1, nxt[maxn][21], l[maxn];
PII a[maxn], b[maxn];

int get(int l, int r) {
    // dbg(l, r);
    if (l > r) return 0;
    int st = lower_bound(::l + 1, ::l + tot + 1, l) - ::l;
    if (st > tot) return 0;
    if (b[st].second > r) return 0;
    int ans = 1;
    for (int i = 19; i >= 0; i--) {
        if (nxt[st][i] == tot + 1) continue;
        if (b[nxt[st][i]].second > r) continue;
        st = nxt[st][i];
        ans += 1 << i;
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    vector<int> lsh;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
        lsh.push_back(a[i].first); lsh.push_back(a[i].second);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    for (int i = 1; i <= n; i++) {
        a[i].first = lower_bound(lsh.begin(), lsh.end(), a[i].first) - lsh.begin() + 1;
        a[i].second = lower_bound(lsh.begin(), lsh.end(), a[i].second) - lsh.begin() + 1;
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n, [](PII a, PII b) {
        if (a.first == b.first) return a.second < b.second;
        return a.first < b.first;
    });
    for (int i = 2; i <= n; i++) {
        while (b[i].second < b[tot].second && tot > 0) tot--;
        b[++tot] = b[i];
    }
    for (int i = 1; i <= tot; i++) dbg(b[i].first, b[i].second);
    for (int i = 1; i <= tot; i++) l[i] = b[i].first;
    for (int i = 1; i <= tot; i++) {
        nxt[i][0] = upper_bound(l + 1, l + 1 + tot, b[i].second) - l;
        dbg(nxt[i][0]);
    }
    for (int i = 0; i < 20; i++) nxt[tot + 1][i] = tot + 1;
    for (int j = 1; j < 20; j++) {
        for (int i = 1; i <= tot; i++) {
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        }
    }
    printf("%d\n", get(0, (int)lsh.size() + 1));
    vector<int> v;
    set<PII> st; st.insert({0, 0}); st.insert({(int)lsh.size() + 1, (int)lsh.size() + 1});
    for (int i = 1; i <= n; i++) {
        auto it = st.lower_bound(a[i]), it2 = it; it2--;
        int l1 = it2->second, r1 = a[i].first, l2 = a[i].second, r2 = it->first;
        dbg(l1, r1, l2, r2);
        if (l1 >= r1 || l2 >= r2) continue;
        if (get(l1 + 1, r1 - 1) + get(l2 + 1, r2 - 1) + 1 == get(l1 + 1, r2 - 1)) {
            v.push_back(i);
            st.insert(a[i]);
        }
    }
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) putchar(' ');
        printf("%d", v[i]);
    }
    return 0;
}