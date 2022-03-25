#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 100000 + 5;

struct node {
    int l, r, tp, id;
    bool operator<(const node& b) {
        if (l != b.l) return l < b.l;
        return tp < b.tp;
    }
};

int b[maxn];
void update(int i, int x) {
    for (; i < maxn; i += i & -i) b[i] += x;
}
int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += b[i];
    return r;
}

int n, q, a[maxn], pos[maxn], ans[maxn];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), pos[a[i]] = i;
    vector<node> ev;
    for (int i = 1; i <= n; i++) {
        for (int j = i + i; j <= n; j += i) {
            int st = min(pos[i], pos[j]), ed = max(pos[i], pos[j]);
            ev.push_back({-st, ed, 0, 0});
        }
    }
    for (int i = 1, l, r; i <= q; i++) {
        scanf("%d%d", &l, &r);
        ev.push_back({-l, r, 1, i});
    }
    sort(ev.begin(), ev.end());
    for (auto x: ev) {
        if (x.tp == 0) {
            update(x.r, 1);
        } else if (x.tp == 1) {
            ans[x.id] = query(x.r);
        }
    }
    for (int i = 1; i <= q; i++) printf("%d%c", ans[i], " \n"[i == q]);
    return 0;
}