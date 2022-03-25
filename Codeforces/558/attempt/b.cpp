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

int n, a[maxn], bag[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        bag[a[i]]++;
        map<int,int> mp;
        for (int j = 1; j <= 10; j++) if (bag[j]) mp[bag[j]]++;
        if ((int)mp.size() == 1) {
            if (mp.begin()->first == 1) ans = i;
            if (mp.begin()->second == 1) ans = i;
        } else if ((int)mp.size() == 2) {
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
        dbg(i, ans);
    }
    cout << ans;
    return 0;
}