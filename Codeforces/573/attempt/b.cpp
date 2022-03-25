#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
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

int n, a[maxn];
vector<int> b;

int main() {
    scanf("%d", &n);
    int zeros = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (a[i] == 0) zeros++;
        else b.push_back(a[i]);
    }
    if (zeros == n) return puts("cslnb"), 0;
    sort(b.begin(), b.end());
    int m = (int)b.size(), last = 0, same = 0;
    for (int i = 1; i < m; i++) if (b[i] == b[i - 1]) same++;
    if (same >= 2) return puts("cslnb"), 0;
    
    if (zeros) last++;
    ll sum = 0;
    for (int i = 0; i < m; i++) {
        // sum += b[i] - (i + 1);
        if (b[i] > last) {
            sum += b[i] - last;
            dbg(i, last, b[i]);
            ++last;
        } else if (b[i] == last) {
            ++last;
        } else if (b[i] < last) {
            assert(0);
        }
    }
    dbg(sum);
    if (sum % 2) puts("sjfnb");
    else puts("cslnb");
    return 0;
}