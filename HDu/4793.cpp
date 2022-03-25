#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const double eps = 1e-4;

double Rm, R, r, x, y, vx, vy;
int dcmp(double x){ if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;}
struct point{
    double x, y;
    point(double x, double y): x(x), y(y){}
    point operator + (const point& b){return point(x + b.x, y + b.y);}
    point operator - (const point& b){return point(x - b.x, y - b.y);}
    point operator * (const double& p){return point(x * p, y * p);}
    double length(){return sqrt(x * x + y * y);}
};
double dot(const point& a, const point& b){return a.x * b.x + a.y * b.y;}
double cross(const point& a, const point& b){return a.x * b.y - a.y * b.x;}
double getdis(point p, point a, point b){
    point v1 = b - a, v2 = p - a;
    return fabs(cross(v1, v2)) / v1.length();
}

int main(){
    while (cin >> Rm >> R >> r >> x >> y >> vx >> vy){
        if (dot(point(x, y), point(vx, vy)) >= 0){
            printf("0.000\n"); continue;
        }
        R += r; Rm += r;
        point st = {x, y}, ed = {x + vx, y + vy}, o = {0, 0};
        double d = getdis(o, st, ed);
        // printf("%.3f\n", d);
        // printf("%d\n", dcmp(d - Rm));
        if (dcmp(d - R) >= 0){
            printf("0.000\n");
        }
        else if (dcmp(d - Rm) >= 0){
            // printf("%.3f\n", d - Rm);
            double res = 2.0 * sqrt(R * R - d * d) / sqrt(vx * vx + vy * vy);
            printf("%.3f\n", res);
        }
        else{
            double d1 = 2 * sqrt(R * R - d * d), d2 = 2.0 * sqrt(Rm * Rm - d * d);
            double res = (d1 - d2) / sqrt(vx * vx + vy * vy);
            printf("%.3f\n", res);
        }
    }
    return 0;
}