#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
using namespace std;
const int MAXN = 3e5 + 10;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, Q;
int belong[MAXN], block;
struct Query {
    int l, r, ID, lca, ans;
    bool operator < (const Query &rhs) const{
        return belong[l] == belong[rhs.l] ? r < rhs.r : belong[l] < belong[rhs.l];
    //    return belong[l] < belong[rhs.l];
    }
}q[MAXN];
vector<int>v[MAXN];
int a[MAXN], date[MAXN];
void Discretization() {
    sort(date + 1, date + N + 1);
    int num = unique(date + 1, date + N + 1) - date - 1;
    for(int i = 1; i <= N; i++) a[i] = lower_bound(date + 1, date + num + 1, a[i]) - date;   
}
int deep[MAXN], top[MAXN], fa[MAXN], siz[MAXN], son[MAXN], st[MAXN], ed[MAXN], pot[MAXN], tot;
void dfs1(int x, int _fa) {
    fa[x] = _fa; siz[x] = 1;
    st[x] = ++ tot; pot[tot] = x;
    for(int i = 0; i < v[x].size(); i++) {
        int to = v[x][i];
        if(deep[to]) continue;
        deep[to] = deep[x] + 1;
        dfs1(to, x);
        siz[x] += siz[to];
        if(siz[to] > siz[son[x]]) son[x] = to;
    }
    ed[x] = ++tot; pot[tot] = x;
}
void dfs2(int x, int topfa) {
    top[x] = topfa;
    if(!son[x]) return ;
    dfs2(son[x], topfa);
    for(int i = 0; i < v[x].size(); i++) {
        int to = v[x][i];
        if(top[to]) continue;
            dfs2(to, to);
    }
}
int GetLca(int x, int y) {
    while(top[x] != top[y]) {
        if(deep[top[x]] < deep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return deep[x] < deep[y] ? x : y;
}
 
struct Node {
    int id, z, f;
};
vector<int> d[MAXN];
vector<Node> qry[MAXN];
int ans[MAXN];
int cur[MAXN];
int val[MAXN];
void dfs(int u, int fa){
  // dbg(u, fa, val[u]);
  // for (auto& x: d[val[u]]) dbg(x);
    for(auto x : d[val[u]]) cur[x]++;
    for(auto p : qry[u]) ans[p.id] += cur[p.z] * p.f;
    for(auto vv : v[u]) {
        if(vv == fa) continue;
        dfs(vv, u);
    }
    for(auto x : d[val[u]]) cur[x]--;
}
void DealAsk() {
    for(int i = 1; i <= Q; i++) {
        int x = read(), y = read(), z = read();
        if(st[x] > st[y]) swap(x, y);
        int _lca = GetLca(x, y);
        q[i].ID = i;
        if(_lca == x) q[i].l = st[x], q[i]. r = st[y];
        else q[i].l = ed[x], q[i].r = st[y], q[i].lca = _lca;
 
        ans[i] = val[_lca] % z == 0;
 
        qry[x].push_back({i, z, 1}), qry[y].push_back({i, z, 1}), qry[_lca].push_back({i, z, -2});
    }
    dfs(1, 0);
}
int Ans, out[MAXN], used[MAXN], happen[MAXN];
void add(int x) {
    if(++happen[x] == 1) Ans++;
}
void delet(int x) {
    if(--happen[x] == 0) Ans--;
}
void Add(int x) {
    used[x] ? delet(a[x]) : add(a[x]); used[x] ^= 1;
}
void Mo() {
    sort(q + 1, q + Q + 1);
    int l = 1, r = 0, fuck = 0;
    for(int i = 1; i <= Q; i++) {
        while(l < q[i].l) Add(pot[l]), l++, fuck++;
        while(l > q[i].l) l--, Add(pot[l]), fuck++;
        while(r < q[i].r) r++, Add(pot[r]), fuck++;
        while(r > q[i].r) Add(pot[r]), r--, fuck++;
        if(q[i].lca) Add(q[i].lca);
        q[i].ans = Ans;
        if(q[i].lca) Add(q[i].lca);
    }
    for(int i = 1; i <= Q; i++) out[q[i].ID] = q[i].ans;
}
void init(int n) {
    for(int i = 0; i < MAXN;i++) deep[i] = top[i] = fa[i] = siz[i] = son[i] = st[i] = ed[i] = pot[i] = tot =0;
    for(int i = 0; i < MAXN; i++) v[i].clear();
    for(int i = 0; i < MAXN; i++) used[i] = 0, happen[i] = 0;
    Ans = 0;
    for(int i = 0; i < MAXN; i++) qry[i].clear();
    for(int i = 0; i < MAXN; i++) cur[i] = 0;
    for(int i = 0; i < MAXN; i++) ans[i] = out[i] = 0;
}
int T;
int main() {
    for(int i = 1; i <= 200000; i++) {
        for(int j = i; j <= 200000; j += i) d[j].push_back(i);
    }
    T=read();
    int cas = 1;
    while(T--) {
        tot = 0;
        N = read();
        init(N);
        block = 305;
        //block = pow(N, 0.66666666666);
        //block = sqrt(N);
        for(int i = 1; i <= N; i++) a[i] = date[i] = read(), val[i] = a[i];
        for(int i = 1; i <= N * 2; i++) belong[i] = i / block + 1;
        Discretization();
        for(int i = 1; i <= N; i++) v[i].clear(), qry[i].clear(),son[i] = 0;
        for(int i = 1; i <= N - 1; i++) {
            int x = read(), y = read();
            v[x].push_back(y); v[y].push_back(x);
        }
        Q=read();
        deep[1] = 1; dfs1(1, 0);
        dfs2(1, 1);
        DealAsk();
        Mo();
        printf("Case #%d:\n", cas++);
        for(int i = 1; i <= Q; i++){
            //cout<<ans[i]<<endl;
            printf("%d\n", ans[i] ^ out[i]);
        }
    }
    return 0;
}
