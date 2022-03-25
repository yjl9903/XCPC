#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, nn, a[maxn];

struct Line {
    int x, y, sym;
    bool operator<(const Line& b) const {
        return x < b.x;
    }
};
struct Query {
    int x, b, t;
    bool operator<(const Query& b) const {
        return x < b.x;
    }
};

void update(int i, int x) {
    for (; i <= nn; i += i & -i) a[i] += x;
}
int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
}

int main() {
    scanf("%d", &n);
    int ans = 0;
    vector<int> lsh;
    vector<Line> upd;
    vector<Query> qry;
    for (int i = 1, x1, x2, y1, y2; i <= n; i++) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        upd.push_back({x1, y1, 1});
        upd.push_back({x1, y2, 1});
        upd.push_back({x2 + 1, y1, -1});
        upd.push_back({x2 + 1, y2, -1});
        qry.push_back({x1, y1, y2});
        qry.push_back({x2, y1, y2});

        lsh.push_back(y1); lsh.push_back(y2);
    }

    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nn = (int)lsh.size();
    auto gid = [&](int x) {
        return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
    };
    
    sort(upd.begin(), upd.end());
    sort(qry.begin(), qry.end());
    int p = 0, m = (int)upd.size();
    for (auto& q: qry) {
        while (p < m && upd[p].x <= q.x) {
            int x = gid(upd[p].y);
            update(x, upd[p].sym);
            p++;
        }
        int b = gid(q.b), t = gid(q.t);
        if (query(t) - query(b - 1) > 2) {
            ans = 1; break;
        }
    }

    cout << ans;
    return 0;
}