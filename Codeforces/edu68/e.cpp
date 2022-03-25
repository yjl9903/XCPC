#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int offset = 5001;
const int maxn = 100000 + 20;

int tr[maxn];
void update(int i, int x) {
    for (; i < maxn; i += i & -i) tr[i] += x;
}
int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += tr[i];
    return r;
}

struct SegX {
    int x, y1, y2;
    bool operator<(const SegX& b) const {
        return x < b.x;
    }
};
struct SegY {
    int y, x1, x2;
};
struct Event {
    int x, y, tp;
    bool operator<(const Event& b) const {
        return x < b.x;
    }
};

int n;
vector<SegX> vx;
vector<SegY> vy;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 += offset; y1 += offset;
        x2 += offset; y2 += offset;
        if (x1 == x2) {
            if (y1 > y2) swap(y1, y2);
            vx.push_back({x1, y1, y2});
        } else {
            if (x1 > x2) swap(x1, x2);
            vy.push_back({y1, x1, x2});
        }
    }
    sort(vx.begin(), vx.end());
    int xn = (int)vx.size(), yn = (int)vy.size();
    ll ans = 0;
    for (int i = 0; i < xn; i++) {
        vector<Event> ev;
        int tx = vx[i].x, ty1 = vx[i].y1, ty2 = vx[i].y2;
        for (auto& seg: vy) {
            if (seg.x1 <= tx && tx <= seg.x2 && ty1 <= seg.y && seg.y <= ty2) {
                ev.push_back({seg.x1, seg.y, 1});
            }
        }
        sort(ev.begin(), ev.end());
        int sz = (int)ev.size(), tot = -1;
        for (int j = 0; j < i; j++) {
            while (tot + 1 < sz && ev[tot + 1].x <= vx[j].x) {
                tot++; update(ev[tot].y, 1);
            }
            int cnt = query(vx[j].y2) - query(vx[j].y1 - 1);
            ans += 1ll * cnt * (cnt - 1) / 2ll;
        }
        for (int i = 0; i <= tot; i++) update(ev[i].y, -1);
    }
    cout << ans;
    return 0;
}