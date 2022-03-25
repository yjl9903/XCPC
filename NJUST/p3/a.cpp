#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const long double eps = 1e-5;

long double r;
struct Point{
    long double x, y;
    Point(long double x = 0, long double y = 0): x(x), y(y){}
};
typedef Point Vector;

Vector operator + (Vector a, Vector b){ return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b){ return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, long double p){ return Vector(a.x * p, a.y * p); }
Vector operator / (Vector a, long double p){ return Vector(a.x / p, a.y / p); }
bool operator < (const Point& a, const Point& b){ return a.x < b.x || (a.x == b.x && a.y < b.y); }
inline int dcmp(long double x){ // long double大小比较，考虑精度eps
    if (abs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
long double dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; }
long double length(Vector a){ return sqrt(a.x * a.x + a.y * a.y); }
long double cross(Vector a, Vector b){ return a.x * b.y - a.y * b.x; }
long double angle(Vector a, Vector b){ return acos(dot(a, b) / length(a) / length(b)); }
Vector rotate(Vector a, long double rad){ return Vector(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad)); }
long double getd(Point p, Point a, Point b){
    Vector v1 = b - a, v2 = p - a;
    return abs(cross(v1, v2)) / length(v1);
}

int getLineCircleIntersection (Point p, Vector v, Point O, long double& t1, long double& t2) {
    long double a = v.x, b = p.x - O.x, c = v.y, d = p.y - O.y;
    long double e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - r * r;
    long double delta = f * f - 4 * e * g;
    if (dcmp(delta) < 0) return 0;
    if (dcmp(delta) == 0) {
        t1 = t2 = -f / (2 * e);
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2 * e);
    t2 = (-f + sqrt(delta)) / (2 * e);
    return 2;
}

bool check(Point o, Point a, Point v, Point b){
    long double t1, t2;
    int c = getLineCircleIntersection(a, v, o, t1, t2);
    if (c == 1 || c == 0) return dcmp(cross(b - a, v)) == 0;
    Point x1 = a + v * t1, x2 = a + v * t2;
    if (dcmp(dot(x1 - a, o - a)) <= 0) swap(x1, x2);
    // cout << x1.x << ' ' << x1.y << endl;
    // cout << x2.x << ' ' << x2.y << endl;
    
    if (dcmp(cross(a - x1, o - x1)) == 0){
        if (dcmp(dot(b - o, a - o)) >= 0) return 1;
        return 0;
    }

    long double d1 = (angle(a - x1, x1 - o)), d2 = (angle(b - x1, x1 - o));
    Vector s = rotate(a - x1, -2 * d1);
    // cout << d1 << endl;
    if (dcmp(cross(s, b - x1)) == 0) return 1;
    else return 0;
    // cout << d1 << ' ' << d2 << ' ' << dcmp(d1 - d2) << endl;
    // if (dcmp(d1) == 0){
    //     if (dcmp(cross(b - a, v)) == 0 && dcmp(dot(b - o, a - o)) > 0) return 1;  
    // }

    // if (dcmp(cross(b - a, v)) == 0){
    //     // if (dcmp(dot(b - o, x1 - o))) return 1;
    //     if (dcmp(dot(a - b, x1 - b)) < 0) return 1;
    //     return 0;
    // }

    // if (dcmp(d1 - d2) == 0) return 1;
    // else return 0;
}

int main(){
    Point o, a, v, b;
    int T, kase = 0; cin >> T;
    while (T--){
        cin >> o.x >> o.y >> r >> a.x >> a.y >> v.x >> v.y >> b.x >> b.y;
        cout << "Case #" << ++kase << ": ";
        long double dis = getd(o, a, a + v);
        
        if (dcmp(dis - r) >= 0){
            long double c = cross(b - a, v), d = dot(b - a, v - a);
            if (dcmp(c) == 0 && dcmp(d) >= 0){
                cout << "Yes";
            }
            else {
                cout << "No";
            }
        }
        else{
            cout << (check(o, a, v, b) ? "Yes" : "No");
        }
        cout << endl;
    }
    return 0;
}