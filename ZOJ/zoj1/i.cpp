#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
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
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 500000 + 5;

int n, q, a[maxn], l[maxn], r[maxn];
set<PII> st;
set<int> pos[maxn];
map<int,int> mp; int tot = 0;
int gid(int x) {
    if (mp[x]) return mp[x];
    return mp[x] = ++tot;
}
void insert(int x, int p) {
    x = gid(x);
    if (l[x] == 0) {
        l[x] = r[x] = p;
        // st.insert({x, p, p});
        st.insert({0, x});
        pos[x].clear();
        pos[x].insert(p);
    } else {
        // st.erase({x, l[x], r[x]});
        st.erase({r[x] - l[x], x});
        l[x] = min(l[x], p);
        r[x] = max(r[x], p);
        st.insert({r[x] - l[x], x});
        // st.insert({x, l[x], r[x]});
        pos[x].insert(p);
    }
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &q);
        st.clear(); tot = 0; mp.clear(); ms(l, 0);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            insert(a[i], i);
        }
        int op, x, y;
        while (q--) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d", &x, &y);
                int t = gid(a[x]);
                pos[t].erase(x);
                if (!pos[t].empty()) {
                    st.erase({r[t] - l[t], t});
                    // st.erase({t, l[t], r[t]});
                    l[t] = *(pos[t].begin());
                    r[t] = *(pos[t].rbegin());
                    st.insert({r[t] - l[t], t});
                }
                a[x] = y;
                insert(y, x);
            } else if (op == 2) {
                PII t = *st.rbegin();
                if (t.first) printf("%d\n", t.first);
                else puts("-1");
            }
        }
    }
    return 0;
}