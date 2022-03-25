#include<bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
typedef long long ll;
const int maxn=300005;

int tr[maxn];
inline int lowbit(int x) {
    return x & -x;
}
inline void update(int i, int x) {
    for (; i < maxn; i += lowbit(i)) tr[i] += x;
}
inline void update(int l, int r, int x) {
    update(l, x); update(r + 1, -x);
}
inline int query(int i) {
    int r = 0;
    for (; i; i -= lowbit(i)) r += tr[i];
    return r;
}

int T;
int n,m;
int c[maxn];
int a[maxn], b[maxn];

int main(){
    scanf("%d",&T);
    int cas = 0;
    while(T--) {
        scanf("%d%d",&n,&m);
        vector<int> lsh;
        for(int i=1;i<=n;i++) scanf("%d%d",a+i,b+i),lsh.push_back(a[i]),lsh.push_back(b[i]);
        for(int i=1;i<=m;i++) scanf("%d",c+i),lsh.push_back(c[i]);
        sort(lsh.begin(),lsh.end());
        lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
        for(int i=1;i<=n;i++) {
            a[i]=lower_bound(lsh.begin(),lsh.end(),a[i])-lsh.begin()+1;
            b[i]=lower_bound(lsh.begin(),lsh.end(),b[i])-lsh.begin()+1;
        }
        for(int i=1;i<=m;i++) c[i]=lower_bound(lsh.begin(),lsh.end(),c[i])-lsh.begin()+1;
        for (int i = 1; i <= n; i++) {
            // dbg(a[i], b[i]);
            update(a[i], b[i], 1);
        }
        int ans = 0, f = 1;
        for (int i = 1; i <= m; i++) {
            int x = query(c[i]);
            // dbg(i, c[i], x);
            if (x == 0) {
                f = 0; break;
            }
            ans = max(ans, n - x + 1);
        }
        printf("Case #%d: ", ++cas);
        if (!f) puts("IMPOSSIBLE!");
        else printf("%d\n", ans);
        memset(tr, 0, sizeof tr);
        // for (int i = 1; i <= n; i++) {
        //     update(a[i], b[i], -1);
        // }
    }
}