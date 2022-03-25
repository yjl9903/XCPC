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
const int maxn = 1000000 + 5;

int n;
PII a[maxn];
// set<int> st;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i].first), a[i].second = i;
    sort(a + 1, a + 1 + n);
    ll ans = 1e18; PII p = {-1, -1};
    for (int i = 1; i <= 2000; i++) {
        int c = 0; ll tot = 1;
        vector<int> v;
        for (int j = 1; c < 2 && j <= n; j++) {
            if (a[j].first % i) continue;
            c++; tot *= a[j].first;
            v.push_back(a[j].second);
        }
        if (c < 2) continue;
        if (tot / i < ans) ans = tot / i, p = make_pair(v[0], v[1]);
        // dbg(i, tot, a[v[0]], a[v[1]]);
    }
    // cout << ans << endl;
    if (p.first > p.second) swap(p.first, p.second);
    cout << p.first << ' ' << p.second;
    return 0;
}