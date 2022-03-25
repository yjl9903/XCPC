#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;
ull sum, a[maxn];

int main() {
    scanf("%d%llu", &n, &sum);
    for (int i = 0; i < n; i++) scanf("%llu", a + i);
    vector<pair<ull,int> > v;
    int half = n / 2, half2 = n - n / 2, ok = 0;
    vector<int> ans(n, 0);
    for (int s = 0; s < (1 << half); s++) {
        ull tot = 0;
        int flag = 1;
        for (int j = 0; j < half; j++) {
            if (s >> j & 1) {
                tot += a[j];
                if (tot > sum) {
                    flag = 0; break;
                }
            }
        }
        if (flag) {
            v.push_back({tot, s});
            if (tot == sum) {
                ok = 1;
                for (int i = 0; i < half; i++) {
                    if (s >> i & 1) {
                        ans[i] = 1;
                    }
                }
                break;
            }
        }
    }
    if (ok) {
        for (int x: ans) putchar('0' + x);
        return 0;
    }
    sort(v.begin(), v.end());
    for (int s = 0; s < (1 << half2); s++) {
        ull tot = 0; int flag = 1;
        for (int j = 0; j < half2; j++) {
            if (s >> j & 1) {
                tot += a[j + half];
                if (tot > sum) {
                    flag = 0; break;
                }
            }
        }
        if (flag) {
            auto it = lower_bound(v.begin(), v.end(), (pair<ull,int>){ sum - tot, 0 });
            if (it != v.end() && it->first + tot == sum) {
                for (int i = 0; i < half; i++) {
                    if (it->second >> i & 1) {
                        ans[i] = 1;
                    }
                }
                for (int i = 0; i < half2; i++) {
                    if (s >> i & 1) {
                        ans[i + half] = 1;
                    }
                }
                break;
            }
        }
    }
    for (int x: ans) putchar('0' + x);
    return 0;
}