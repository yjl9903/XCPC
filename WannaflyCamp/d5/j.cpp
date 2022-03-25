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
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;
const double eps = 1e-5;

struct Point{
    ll x, y;
    Point(int x = 0, int y = 0): x(x), y(y){}
} a[maxn];
typedef Point Vector;

Vector operator + (Vector a, Vector b){ return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b){ return Vector(a.x - b.x, a.y - b.y); }
bool operator < (const Point& a, const Point& b){ return a.x < b.x || (a.x == b.x && a.y < b.y); }

struct Line {
    Point a, b;
};

ll xmult(Point p1, Point p2, Point p0){
    return 1ll * (p1.x - p0.x) * (p2.y - p0.y) - 1ll * (p2.x - p0.x) * (p1.y - p0.y);
}
ll opposite_side(Point p1, Point p2, Line l){
    ll a = xmult(l.a, p1, l.b);
    ll b = xmult(l.a, p2, l.b);
    if ((a > 0 && b < 0) || (a < 0 && b > 0)) return 1;
    return 0;
    // return xmult(l.a, p1, l.b) * xmult(l.a, p2, l.b) < -eps;
}
ll intersect_ex(Line u, Line v){
    return opposite_side(u.a,u.b,v) && opposite_side(v.a,v.b,u);
}

bool issame(Point a, Point b) {
    if (a.x == b.x && a.y == b.y) return 1;
    return 0;
}

ll dot_online_in(Point p, Line l){
    return xmult(p,l.a,l.b) == 0 && (l.a.x - p.x) * (l.b.x - p.x) <= 0 && (l.a.y-p.y) * (l.b.y-p.y) <= 0;
}
ll dot_online_ex(Point p, Line l){
    return dot_online_in(p,l) && ((p.x-l.a.x)|| (p.y-l.a.y))&&((p.x-l.b.x) || (p.y-l.b.y));
}

int n, m;
vector<PII> eg;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        eg.push_back({u, v});
    }
    for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].x, &a[i].y);
    int ans = 0;
    for (int i = 0; i < eg.size(); i++) {
        for (int j = i + 1; j < eg.size(); j++) {
            int u = eg[i].first, v = eg[i].second;
            int u1 = eg[j].first, v1 = eg[j].second;
            if (issame(a[u], a[u1]) || issame(a[u], a[v1]) || issame(a[v], a[u1]) || issame(a[v], a[v1])) continue;
            if (intersect_ex({a[u], a[v]}, {a[u1], a[v1]})) {
                ans++;
            } 
            // else if (dot_online_ex(a[u], {a[u1], a[v1]}) || dot_online_ex(a[v], {a[u1], a[v1]})) {
            //     ans++;
            // } else if (dot_online_ex(a[u1], {a[u], a[v]}) || dot_online_ex(a[v1], {a[u], a[v]})) {
            //     ans++;
            // }
        }
    }
    cout << ans << endl;
    return 0;
}