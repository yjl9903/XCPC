#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
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
const int maxn = 200000 + 5;

int tr[maxn];
int lowbit(int x) {
    return x & -x;
}
void update(int i, int x) {
    for (; i; i -= lowbit(i)) tr[i] += x;
}
void clear(int i) {
    for (; i; i -= lowbit(i)) tr[i] = 0;
}
int query(int i) {
    int r = 0;
    for (; i < maxn; i += lowbit(i)) r += tr[i];
    return r;
}

int qcnt, ans[maxn];
struct Que {
    int x, y, z, id;
} q[maxn], b[maxn];
map< pair<int,PII> ,int> id;
int gid(pair<int,PII> a) {
    if (id.count(a)) return id[a];
    return id[a] = ++qcnt;
}
bool cmp(Que a, Que b) {
    if (a.y == b.y) return a.z > b.z;
    return a.y > b.y;
}
void cdq(int l, int r) {
    if (l >= r) return ;
    int m = (l + r) / 2;
    cdq(l, m); cdq(m + 1, r); 
    for (int i = l; i <= r; i++) b[i] = q[i];
    sort(b + l, b + m + 1, cmp);
    sort(b + m + 1, b + r + 1, cmp);
    int j = l;
    for (int i = m + 1; i <= r; i++) {
        for (; j <= m && b[j].y >= b[i].y; j++) update(b[j].z, 1);
        ans[b[i].id] += query(b[i].z);
    }
    for (j--; j >= l; j--) clear(b[j].z);
}

int n, m;
ll cnt[maxn];
vector<int> b1[maxn];
vector<PII> b2[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1, a, b; i <= n; i++) {
            scanf("%d%d", &a, &b); b1[b].push_back(a);
        }
        for (int i = 1, a, b, c; i <= m; i++) {
            scanf("%d%d%d", &a, &b, &c); b2[c].push_back({a, b});
        }
        qcnt = 0; id.clear();
        for (int i = 1; i <= (int)1e5; i++) {
            if (b1[i].empty()) continue;
            if (b2[i].empty()) continue;
            int mx = *max_element(b1[i].begin(), b1[i].end());
            int c = count(b1[i].begin(), b1[i].end(), mx);
            map<PII,int> mp;
            vector<PII> qc;
            for (auto x: b2[i]) mp[x]++;
            for (auto x: mp) qc.push_back(x.first);
            for (auto x: qc) {
                int id = gid({ mx, make_pair(x.first, x.second) });
                ans[id] = 0; cnt[id] += 1ll * c * mp[x];
                q[id] = (Que){ mx, x.first, x.second, id };
            }
            b1[i].clear(); b2[i].clear();
        }
        // for (int i = 1; i <= qcnt; i++) {
        //     dbg(q[i].x, q[i].y, q[i].z);
        // }
        sort(q + 1, q + 1 + qcnt, [](Que a, Que b) {
            if (a.x != b.x) return a.x > b.x;
            else if (a.y != b.y) return a.y > b.y;
            return a.z > b.z;
        });
        cdq(1, qcnt); 
        ll res = 0;
        for (int i = 1; i <= qcnt; i++) {
            // dbg(i, ans[i]);
            if (ans[i] == 0) res += cnt[i];
        }
        printf("Case #%d: %lld\n", ++kase, res);
        for (int i = 0; i <= qcnt; i++) cnt[i] = 0;
        for (int i = 1; i <= (int)1e5; i++) b1[i].clear(), b2[i].clear();
    }
    return 0;
}