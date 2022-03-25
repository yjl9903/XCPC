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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, a[maxn], bag[maxn], cnt[maxn], sz = 0;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int ans = 1; map<int,int> mp;
    for (int i = 1; i <= n; i++) {
        if (bag[a[i]]) {
            mp[bag[a[i]]]--;
            if (mp[bag[a[i]]] == 0) sz--, mp.erase(bag[a[i]]);
        }
        bag[a[i]]++;
        mp[bag[a[i]]]++;
        if (mp[bag[a[i]]] == 1) sz++;
        if (sz == 1) {
            if (mp.begin()->first == 1) ans = i;
            if (mp.begin()->second == 1) ans = i;
        } else if (sz == 2) {
            auto it = mp.begin(), it2 = mp.begin(); it2++;
            // dbg(i);
            // dbg(it->first, it->second);
            // dbg(it2->first, it2->second);
            if (it->first - 1 == it2->first || it->first == 1) {
                if (it->second == 1) ans = i;
            }
            if (it2->first - 1 == it->first || it2->first == 1) {
                if (it2->second == 1) ans = i;
            }
        }
    }
    cout << ans;
    return 0;
}