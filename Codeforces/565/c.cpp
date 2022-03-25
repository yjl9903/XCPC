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
const int maxn = 500000 + 5;

int get(int x) {
    if (x == 4) return 0;
    if (x == 8) return 1;
    if (x == 15) return 2;
    if (x == 16) return 3;
    if (x == 23) return 4;
    if (x == 42) return 5;
    return -1;
}

int n, a[maxn];
set<int> bag[6];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        int id = get(a[i]);
        if (id == -1) continue;
        bag[id].insert(i);
    }
    int ans = 0;
    for (int x: bag[0]) {
        int now = x, flag = 1;
        vector<int> v; v.push_back(now);
        for (int j = 1; j < 6; j++) {
            auto it = bag[j].lower_bound(now);
            if (it == bag[j].end()) {
                flag = 0; break;
            }
            now = *it; v.push_back(now);
        }
        if (flag) {
            ans += 6;
            for (int j = 1; j < 6; j++) {
                // dbg(j, v[j]);
                bag[j].erase(v[j]);
            }
        }
    }
    cout << n - ans;
    return 0;
}