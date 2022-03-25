#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <map>
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
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

const double eps = 1e-5;
const double pi = acos(-1.0);

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

inline int dcmp(double x) { 
    // double大小比较，考虑精度eps
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
inline int zero(double x) {
    return fabs(x) < eps;
}

struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y){}
    bool operator<(const Point& b) const {
        return x < b.x;
    }
    bool operator==(const Point& b) const {
        return x == b.x && y == b.y;
    }
};
typedef Point Vector;

Vector operator + (Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b) { return Vector(a.x - b.x, a.y - b.y); }

int cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
ll length(Vector a) { return 1ll * a.x * a.x + 1ll * a.y * a.y; }
int xmult(Point a, Point b, Point c) {
    // 0 -> 三点共线
    // + -> AC 在 AB 的逆时针方向
    // - -> AC 在 AB 的顺时针方向 
    return cross(b - a, c - a);
}

struct Line {
    Point p; Vector v;
    Line(Point a, Point b) : p(a), v(b - a) {}
};

PLL getDistanceToLine(Point p, Point a, Point b) {
    Vector v1 = b - a, v2 = p - a;
    ll x = 1ll * cross(v1, v2) * cross(v1, v2);
    ll y = length(v1);
    if (x == 0) return { 0, 1 };
    else if (x > 0) {
        ll g = gcd(x, y);
        return { x / g, y / g };
    } else {
        ll g = gcd(-x, y);
        return { -x / g, y / g };
    }
}

int n;
Point a[1005];
vector<Line> b, c;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            b.push_back({a[i], a[j]});
        }
    }
    map< PII, vector<PII> > mp;
    for (auto& x: b) {
        if (x.v.x == 0) {
            mp[{0, 1}].push_back({x.p.x, x.p.y});
        } else if (x.v.y == 0) {
            mp[{1, 0}].push_back({x.p.x, x.p.y});
        } else {
            int g = gcd(abs(x.v.x), abs(x.v.y));
            if (1ll * x.v.x * x.v.y > 0) {
                mp[{abs(x.v.x) / g, abs(x.v.y) / g}].push_back({x.p.x, x.p.y});
            } else {
                mp[{-abs(x.v.x) / g, abs(x.v.y) / g}].push_back({x.p.x, x.p.y});
            }
        }
    }
    ll ans = 0; int sum = 0;
    map<PII,int> cnt;
    for (auto& v: mp) {
        dbg(v.first.first, v.first.second);
        // vector<PII> vec;
        // set<PLL> st;
        // PII ed = v.second[0];
        // Point a(v.second[0].first, v.second[0].second);
        // Point b(v.first.first, v.first.second);
        // b = a + b;
        // for (int i = 0; i < (int)v.second.size(); i++) {
        //     Point p(v.second[i].first, v.second[i].second);
        //     PLL h = getDistanceToLine(p, a, b);
        //     if (xmult(p, a, b) < 0) h.first = -h.first;
        //     dbg(h.first, h.second, xmult(p, a, b));
        //     st.insert(h);
        // }
        set<ll> st;
        for (PII x: v.second) {
            st.insert(1ll * v.first.second * x.first - 1ll * v.first.first * x.second);
        }
        sum += (int)st.size();
        cnt[v.first] = (int)st.size();
        dbg(st.size());
    }
    for (auto& x: cnt) {
        ans += 1ll * x.second * (sum - x.second);
    }
    cout << ans / 2;
    return 0;
}