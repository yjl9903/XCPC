#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps = 1e-8;

int dcmp(double x){if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;}
struct point{
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y){}
    point operator + (const point& b){return point(x + b.x, y + b.y);}
    point operator - (const point& b){return point(x - b.x, y - b.y);}
    point operator * (const double& p){return point(x * p, y * p);}
    point operator / (const double& p){return point(x / p, y / p);}
    double length(){return sqrt(x * x + y * y);}
};
double dot(point a, point b){return a.x * b.x + a.y * b.y;}
double cross(point a, point b){return a.x * b.y - a.y * b.x;}
point getNormal(point a){return point(-a.y, a.x);}
point GetLineIntersection(point p, point v, point q, point w){
    point u = p - q;
    double t = cross(w, u) / cross(v, w);
    return p + v * t;
}

int getLineCircle(point p, point v, point o, double r, double& t1, double& t2){
    double a = v.x, b = p.x - o.x, c = v.y, d = p.y - o.y;
    double e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - r * r;
    double delta = f * f - 4 * e * g;
    if (dcmp(delta) < 0) return 0;
    if (dcmp(delta) == 0){
        t1 = t2 = -f / (2 * e);
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2 * e);
    t2 = (-f + sqrt(delta)) / (2 * e);
    return 2;
}
double getPos(point v, point t){
    if (dcmp(v.x) == 0) return t.y / v.y;
    return t.x / v.x;
}
bool online(point v, point b, point a){return dcmp(cross(v, b - a)) == 0;}

int main(){
    point a, v, b, o; double r;
    int T, kase = 0; cin >> T;
    while (T--){
        cin >> o.x >> o.y >> r >> a.x >> a.y >> v.x >> v.y >> b.x >> b.y;
        cout << "Case #" << ++kase << ": ";
        double t1, t2, inf = 1e20, hint = inf;
        int t = getLineCircle(a, v, o, r, t1, t2), flag = 0;

        if (t > 1 && dcmp(t1) >= 0) hint = t1;
        else if (t > 1 && dcmp(t2) >= 0) hint = t2;
        
        if (online(v, b, a)){
            double t = getPos(v, b - a);
            if (dcmp(t) >= 0 && t < hint) flag = 1;
        }
        if (dcmp(hint - inf) < 0){
            point x = a + v * hint;
            point h = getNormal(o - x);
            point T = GetLineIntersection(x, h, b, o - x);
            b = T * 2 - b;

            if (online(v, b, a)){
                double t = getPos(v, b - a);
                if (dcmp(t) >= 0) flag = 1;
            }
        }
        cout << (flag ? "Yes" : "No") << endl;
    }
    return 0;
}