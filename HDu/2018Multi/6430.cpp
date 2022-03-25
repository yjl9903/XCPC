#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, ans[maxn], fa[maxn], a[maxn];

vector<int> fac[maxn];
int ls[maxn * 800] = {0}, rs[maxn * 800] = {0};
int root[maxn], tot = 0, f;

void update(int k, int l, int r, int& rt){
    if (!rt) rt = ++tot;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (k <= m) update(k, l, m, ls[rt]);
    else update(k, m + 1, r, rs[rt]);
}
int join(int pre, int l, int r, int rt){
    if (!pre || !rt) return pre ^ rt;
    if (l == r) { ans[f] = max(ans[f], l); return rt;}
    int m = (l + r) >> 1;
    ls[rt] = join(ls[pre], l, m, ls[rt]);
    rs[rt] = join(rs[pre], m + 1, r, rs[rt]);
    return rt;
}

int main(){
    for (int i = 1; i < maxn; i++) for (int j = 1; i * j < maxn; j++)
        fac[i * j].push_back(i);
    scanf("%d", &n); ms(ans, -1);
    for (int i = 2; i <= n; i++) scanf("%d", &fa[i]);
    for (int x, i = 1; i <= n; i++) {
        scanf("%d", &x); root[i] = ++tot;
        for (int j = 0; j < fac[x].size(); j++) 
            update(fac[x][j], 1, maxn - 1, root[i]);
    }
    for (int i = n; i >= 1; i--){
        f = fa[i]; root[f] = join(root[i], 1, maxn - 1, root[f]);
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}