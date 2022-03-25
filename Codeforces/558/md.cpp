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
const int maxn = 100000 + 5;

struct Point {
    ll x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {  }
    bool operator<(const Point& b) const {
        return x < b.x || ( x == b.x && y < b.y);
    }
    bool operator==(const Point& b) const {
        return x == b.x && y == b.y;
    }
};
typedef Point Vector;

Vector operator + (Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, ll p) { return Vector(a.x * p, a.y * p); }

ll dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
ll length(Vector a) { return sqrt(a.x * a.x + a.y * a.y); }
ll distance(Point a, Point b) { return length(b - a); }
ll cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
ll xmult(Point a, Point b, Point c) {
    // 0 -> 三点共线
    // + -> AC 在 AB 的逆时针方向
    // - -> AC 在 AB 的顺时针方向 
    return cross(b - a, c - a);
}
ll area2(Vector a, Vector b, Vector c) { return cross(b - a, c - a); }
double angle(Vector a, Vector b) { return atan2(b.x - a.x, b.y - a.y); }

// 直线表示： 已知直线上两个不同点A和B，则方向向量为（B-A），参数方程为 A + (B - A) t
// 直线 t 无限制，射线 t > 0，线段 t 在 0 到 1 之间
struct Line {
    Point p; Vector v;
    Line(Point a, Point b) : p(a), v(b - a) {}
};


int main() {
    
    return 0;
}