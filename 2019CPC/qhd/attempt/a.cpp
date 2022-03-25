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
const int maxn = 2000 + 5;

const double eps = 1e-5;
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
    Point(double x = 0, double y = 0): x(x), y(y) {}

    int quad() {
        if (dcmp(x) >= 0 && dcmp(y) >= 0) return 1;
        if (dcmp(x) < 0 && dcmp(y) >= 0) return 2;
        if (dcmp(x) < 0 && dcmp(y) < 0) return 3;
        if (dcmp(x) >= 0 && dcmp(y) < 0) return 4;
    }
};
typedef Point Vector;

Vector operator + (Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, double p) { return Vector(a.x * p, a.y * p); }
Vector operator / (Vector a, double p) { return Vector(a.x / p, a.y / p); }
bool operator < (const Point& a, const Point& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }

bool operator == (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}

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

int n, q, ans[maxn];

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        vector<Point> a;
        for (int i = 0, x, y; i < n; i++) {
            scanf("%d%d", &x, &y);
            a.push_back({x, y});
        }
        for (int i = 0, x, y; i < q; i++) {
            scanf("%d%d", &x, &y);
            vector<Vector> vec;
            for (auto& p: a) vec.push_back((Point){x, y} - p);
            sort(vec.begin(), vec.end(), [](Point a, Point b) -> int {
                if (a.quad() != b.quad()) return a.quad() < b.quad();
                return cross(a, b) > eps;
            });
            int j = 0, last = 0;
            int& ans = ::ans[i];
            for (int i = 0; i < n; i++) {
                if (i && zero(cross(vec[i], vec[i - 1])) && dot(vec[i], vec[i - 1]) > eps) {
                    ans += last; continue;
                }
                int c = 0;
                while (cross(vec[i], vec[j]) > eps && dot(vec[i], vec[j]) > -eps) {
                    j++; c++;
                }
            }
        }
    }
    return 0;
}