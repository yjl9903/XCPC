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
const int maxn = 1000000 + 5;

vector<int> edge[maxn];
vector<int> tag[maxn], sub[maxn];
int n, k, a[maxn], fa[maxn], dep[maxn];

int s[maxn], tot;
void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    s[++tot] = -u;
    int l = 0 - *lower_bound(s + 1, s + 1 + tot, -(u + k - 1));
    // dbg(u, l, dep[u] - dep[l] + 1);
    // tag[u].push_back(dep[u] - dep[l] + 1);
    // sub[l + 1].push_back(dep[u] - dep[l] + 1);
    for (int& v: edge[u]) {
        dfs(v, u);
    }
    tot--;
}

int ans[maxn];

int main() {
    scanf("%d%d", &n, &k);
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        while (!st.empty() && a[i] > a[st.back()]) {
            fa[st.back()] = i; 
            edge[i].push_back(st.back());
            st.pop_back();
        }
        st.push_back(i);
    }
    for (int i = 1; i <= n; i++) if (!fa[i]) dfs(i, 0);
    // multiset<int> ms;
    // for (int i = 1; i <= k; i++) {
    //     for (int& x: tag[i]) {
    //         ms.insert(x);
    //     }
    //     ans[1] = max(ans[1], *ms.rbegin());
    // }
    // for (int i = 2; i + k - 1 <= n; i++) {
    //     for (int& x: sub[i - 1]) ms.erase(ms.find(x));
    // }
    return 0;
}