#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
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
const int maxn = 400000 + 5;

int n, m, a[maxn];

int check(int x) {
    ll sum = 0, pd = n / x;
    for (int i = 0, k = 0; i < n; i += x, k++) {
        for (int j = i; j < i + x; j++) sum += max(0, a[j] - k);
    }
    // dbg(sum);
    // for (int i = n / x * x; i < n; i++) {
    //     sum += max(0, a[i] - pd);
    // }
    dbg(x, sum);
    return sum >= m;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n); reverse(a, a + n);
    int ans = -1, l = 1, r = n;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (check(m)) ans = m, r = m - 1;
        else l = m + 1;
    }
    cout << ans << endl;
    // for (int i = 1; i <= n; i++) check(i);
    return 0;
}