#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
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
const int maxn = 500000 + 5;

int n, c, a[maxn], pre[maxn], suf[maxn];
map< int,vector<int> > mp;

int main() {
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), mp[a[i]].push_back(i);
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + int(a[i] == c);
    int ans = pre[n];
    for (auto& x: mp) {
        if (x.first == c) continue;
        auto v = x.second;
        int mx = -1e9, i = 0;
        for (int& x: v) {
            mx = max(mx, pre[x] - i);
            ans = max(ans, pre[n] - pre[x] + i + 1 + mx);
            i++;
        }
    }
    cout << ans << endl;
    return 0;
}