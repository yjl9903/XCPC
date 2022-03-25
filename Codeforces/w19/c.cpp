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
const int maxn = 200000 + 5;

int n;
char s[maxn];

int main() {
    scanf("%d%s", &n, s);
    int ans = 0, u = 0, r = 0, d = 0, l = 0, dx = 0, dy = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'R') {
            dx++;
            if (l == 1) {
                ans++;
                u = d = l = 0; r = 1;
            } else r = 1;
        }
        if (s[i] == 'L') {
            dx--;
            if (r == 1) {
                ans++;
                u = d = r = 0; l = 1;
            } else l = 1;
        }
        if (s[i] == 'U') {
            dy++;
            if (d == 1) {
                ans++;
                l = r = d = 0; u = 1;
            } else u = 1;
        }
        if (s[i] == 'D') {
            dy--;
            if (u == 1) {
                ans++;
                l = r = u = 0; d = 1;
            } else d = 1;
        }
        dbg(u, d, l, r, ans);
    }
    if (u || d || l || r) ans++;
    // if (dx == 0 && dy == 0) ans--;
    cout << ans << endl;
    return 0;
}