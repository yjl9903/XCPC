#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const int mod = 998244353;
const int maxn = 100000 + 5;

const double eps = 1e-7;
const double pi = acos(-1.0);

inline int dcmp(double x) { 
    // double大小比较，考虑精度eps
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
inline int zero(double x) {
    return fabs(x) < eps;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y){}
};
typedef Point Vector;

Vector operator + (Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, double p) { return Vector(a.x * p, a.y * p); }
Vector operator / (Vector a, double p) { return Vector(a.x / p, a.y / p); }
bool operator < (const Point& a, const Point& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double length(Vector a) { return sqrt(a.x * a.x + a.y * a.y); }
double distance(Point a, Point b) { return length(b - a); }
double angle(Vector a, Vector b) { return acos(dot(a, b) / length(a) / length(b)); }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
double xmult(Point a, Point b, Point c) {
    // 0 -> 三点共线
    // + -> AC 在 AB 的逆时针方向
    // - -> AC 在 AB 的顺时针方向 
    return cross(b - a, c - a);
}

Vector rotate(Vector a, double rad) { 
    return Vector(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad)); 
}
Vector normal(Vector a) { // 计算单位法线，确保a不是零向量
    double l = length(a); return Vector(-a.y / l, a.x / l); 
}
Vector getNormal(Vector a) { return Vector(-a.y, a.x); }

// 直线表示： 已知直线上两个不同点A和B，则方向向量为（B-A），参数方程为 A + (B - A) t
// 直线 t 无限制，射线 t > 0，线段 t 在 0 到 1 之间
struct Line {
    Point p; Vector v;
    Line(Point a, Point b) : p(a), v(b - a) {}
};

int k; double p;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        cin >> k >> p;
        Point start = {0, 0}, end = {80, 0};
        vector<Point> v = {start, end};
        double xs = sqrt(2.0) / 4.0, len = 80.0;
        for (int i = 0; i < k; i++) {
            vector<Point> v2 = {start};
            for (int i = 0; i + 1 < v.size(); i++) {
                Point tot = v[i], nxt = v[i + 1];
                Point r1 = rotate((nxt - tot) * xs, pi / 4.0);
                Point r2 = rotate((tot - nxt) * xs, pi / 4.0);
                // v2.push_back(tot);
                v2.push_back(tot + r1);
                v2.push_back(nxt + r2);
                v2.push_back(nxt);
            }
            v = v2;
            len *= sqrt(2.0);
        }
        len *= p;
        dbg(len);
        Point ans;
        for (int i = 0; i + 1 < v.size(); i++) {
            dbg(v[i].x, v[i].y);
            Point tot = v[i], nxt = v[i + 1];
            double l = distance(v[i], v[i + 1]);
            if (len > l) len -= l;
            else {
                ans = v[i] + (v[i + 1] - v[i]) * len / distance(v[i], v[i + 1]);
                break;
            }
        }
        dbg(len);
        printf("(%.5f, %.5f)\n", ans.x + eps, ans.y + eps);
        // for (int i = 0; i < v.size(); i++) {
        //     dbg(v[i].x, v[i].y);
        // }
    }
    return 0;
}