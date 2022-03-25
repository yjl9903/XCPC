#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, a[maxn];
set<PII> s[2];

int main() {
    scanf("%d", &n);
    int x = 0, f = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (i == 1) x = a[i] % 2;
        else {
            if (a[i] % 2 != x) f = 1;
        }
        // s[a[i] % 2].insert({a[i], i});
    }
    if (f) sort(a + 1, a + 1 + n);
    // for (int i = 1; i <= n; i++) {
    //     dbg(s[0].size(), s[1].size());
    //     int x = a[i] % 2; x ^= 1;
    //     if (s[x ^ 1].count({a[i], i})) s[x ^ 1].erase({a[i], i});
    //     if (s[x].empty()) continue;
    //     auto it = s[x].begin();
    //     if (a[i] < it->first) continue;
    //     a[it->second] = a[i];
    //     s[x ^ 1].insert({a[it->second], it->second});
    //     a[i] = it->first;
    //     s[x].erase(it);
    // }
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    return 0;
}