#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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

int n, x, a[maxn], pre[maxn], suf[maxn];
int first[maxn], last[maxn];

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (first[a[i]] == 0) first[a[i]] = i;
        last[a[i]] = i;
    }
    suf[x + 1] = n + 1;
    for (int i = x; i >= 1; i--) {
        if (first[i] == 0) suf[i] = suf[i + 1];
        else {
            if (last[i] < suf[i + 1]) suf[i] = first[i];
            else suf[i] = 0;
        }
    }
    pre[0] = 0;
    for (int i = 1; i <= x; i++) {
        if (first[i] == 0) pre[i] = pre[i - 1];
        else {
            if (first[i] > pre[i - 1]) pre[i] = last[i];
            else pre[i] = n + 1;
        }
    }
    for (int i = 0; i <= x + 1; i++) dbg(i, pre[i]);
    for (int i = 0; i <= x + 1; i++) dbg(i, suf[i]);
    ll ans = 0;
    for (int i = 1; i <= x + 1; i++) {
        int id = lower_bound(pre, pre + i - 1, suf[i]) - pre;
        dbg(i, suf[i], id, pre[id]);
        ans += id;
    }
    cout << ans << endl;
    return 0;
}