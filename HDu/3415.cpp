#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
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
const ll inf = 1ll << 60;

int n, k, a[maxn], q[maxn]; ll pre[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i + n] = a[i];
        for (int i = 1; i <= 2 * n; i++) pre[i] = pre[i - 1] + a[i];
        int l = 1, r = 0, ansl = 0, ansr = 0; ll ans = -inf;
        for (int i = 1; i <= 2 * n; i++) {
            while (l <= r && pre[i - 1] < pre[q[r]]) r--;
            q[++r] = i - 1;
            while (i - q[l] > k) l++;
            if (pre[i] - pre[q[l]] > ans){
                ans = pre[i] - pre[q[l]];
                ansl = q[l] + 1; ansr = i;
                if (ansr > n) ansr -= n;
            }
        }
        printf("%lld %d %d\n", ans, ansl, ansr);
    }
    return 0;
}