#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;
const double eps = 1e-5;

inline int dcmp(double x){ // double大小比较，考虑精度eps
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}

struct Point{
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y){}
};
typedef Point Vector;

Vector operator + (Vector a, Vector b){ return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b){ return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, double p){ return Vector(a.x * p, a.y * p); }

double dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b){ return a.x * b.y - a.y * b.x; }

Vector getNormal(Vector a){ return Vector(-a.y, a.x); }

bool SegmentProperIntersection(Point a1, Point b1, Point a2, Point b2){
    // 端点重合不算相交，线段A1B1,A2B2是否相交
    double c1 = cross(b1 - a1, a2 - a1), c2 = cross(b1 - a1, b2 - a1);
    double c3 = cross(b2 - a2, a1 - a2), c4 = cross(b2 - a2, b1 - a2);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
bool onSegment(Point p, Point a1, Point a2){
    // 点是否在一条线段上（不包含端点）
    return dcmp(cross(a1 - p, a2 - p)) == 0 && dcmp(dot(a1 - p, a2 - p)) < 0;
}
Point GetLineIntersection(Point p, Vector v, Point q, Vector w){
    // P + tv 和 Q + wv 有唯一交点，当且仅当 cross(v,w) != 0
    Vector u = p - q;
    double t = cross(w, u) / cross(v, w);
    return p + v * t;
}

bool check(Point v, Point p, Point w1, Point w2) {
    return !SegmentProperIntersection(v, p, w1, w2) && !onSegment(w1, v, p) && !onSegment(w2, v, p);
}

Point v, p, w1, w2, m1, m2;

int main() {
    scanf("%lf%lf%lf%lf", &v.x, &v.y, &p.x, &p.y);
    scanf("%lf%lf%lf%lf", &w1.x, &w1.y, &w2.x, &w2.y);
    scanf("%lf%lf%lf%lf", &m1.x, &m1.y, &m2.x, &m2.y);
    bool ans = 0;
    // cout << check(v, p, w1, w2) << ' ' << check(v, p, m1, m2) << endl;
    if (check(v, p, w1, w2)) {
        if (onSegment(m1, v, p) && onSegment(m2, v, p)) {
            ans = 1;
        } else if (check(v, p, m1, m2)) {
            ans = 1;
        } 
    }
    int f1 = dcmp(cross(m2 - m1, v - m1)), f2 = dcmp(cross(m2 - m1, p - m1));
    // cout << f1 << ' ' << f2 << endl;
    if (f1 * f2 > 0) {
        Point fm = getNormal(m2 - m1);
        Point o = GetLineIntersection(v, fm, m1, m2 - m1);
        Point v1 = o * 2 - v;

        if ((dcmp(v.x - v1.x) || dcmp(v.y - v1.y)) && !check(v1, p, m1, m2)) {
            // puts("?");
            Point c = GetLineIntersection(v1, p - v1, m1, m2 - m1);
            if (check(v, c, w1, w2) && check(c, p, w1, w2)) {
                ans = 1;
            }
        }
    }
    if (ans) puts("YES");
    else puts("NO");
    // cout << f1 << ' ' << f2 << endl;
    return 0;
}