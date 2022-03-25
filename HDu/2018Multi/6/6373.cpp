#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
const double g = 9.8;

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
double len(point a){return sqrt(dot(a, a));}
point getNormal(point a){return point(-a.y, a.x);}
point GetLineIntersection(point p, point v, point q, point w){
    point u = p - q;
    double t = cross(w, u) / cross(v, w);
    return p + v * t;
}
double getPos(point v, point t){
    if (dcmp(v.x) == 0) return t.y / v.y;
    return t.x / v.x;
}
bool online(point v, point b, point a){return dcmp(cross(v, b - a)) == 0;}

double a, b, x, y;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%lf%lf%lf%lf", &a, &b, &x, &y);
        double d = y - b / a * (-x);
        if (d <= 0 || x >= 0 || y <= 0){
            puts("0"); continue;
        }
        point v = {0, -sqrt(2 * g * d)};
        point tot = {x, d};
        point s = {a, -b};
        point f = getNormal(s);
        point T = GetLineIntersection(tot + v, f, tot, s) - tot;
        v = T * 2 - v;
        int res = 1;
        while (true){
            double t = 2 * (b / a * v.x + v.y) / g;
            double tx = v.x * t + tot.x;
            if (tx > 0) break;
            res++;
            tot = {v.x * t + tot.x, tot.y + v.y * t - g * t * t / 2};
            v = {v.x, v.y - g * t};
            T = GetLineIntersection(tot + v, f, tot, s) - tot;
            v = T * 2 - v;
        }
        printf("%d\n", res);
    }
    return 0;
}