#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 200000 + 5;

struct node {
    int u, v, w;
    bool operator<(const node& b)const{
        return w > b.w;
    }
};

int n, m, pre[maxn], val[maxn];

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) pre[i] = i;
    priority_queue<node> pq;
    for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        pq.push({u, v, w});
    }
    int ans = 0;
    while (!pq.empty()) {
        node t = pq.top(); pq.pop();
        dbg(t.u, t.v, t.w);
        int x = find(t.u), y = find(t.v);
        if (x == y) { 
            // dbg(val[x], t.w);
            if (val[x] == t.w) ans++;
            continue; 
        }
        pre[y] = x; val[x] = max(max(val[x], val[y]), t.w);
    }
    cout << ans << endl;
    return 0;
}