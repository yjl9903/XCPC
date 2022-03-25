#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, k, h[maxn];
ll cnt[maxn];

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", h + i);
    sort(h, h + n); int top = h[n - 1], but = h[0];
    for (int i = top; i > 0; i--){
        int k = lower_bound(h, h + n, i) - h;
        cnt[i] = cnt[i + 1] + n - k;
    }
    reverse(cnt + 1, cnt + 1 + top); 
    // cnt[top + 1] = 1ll << 60;
    // for (int i = 1; i <= top; i++) cout << cnt[i] << endl; puts("");
    dbg(top, but);
    int ans = 0, tot = 1; ll sum = 0;
    while (tot <= top - but){
        if (sum + k < cnt[tot]){
            // puts("ha");
        }
        else {
            int r = upper_bound(cnt + 1, cnt + 1 + top, sum + k) - cnt;
            sum = cnt[r - 1]; tot = r;
            dbg(r, sum, tot);
        }
        ans++;
    }
    printf("%d", ans);
    return 0;
}