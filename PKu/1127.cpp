#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 15 + 5;
const double eps = 1e-10;

int dcmp(double x){if (abs(x) < eps) return 0; else return (x < 0 ? -1 : 1);}
struct point{
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y){}
}line[maxn][2];
typedef point Vector;
int n, pre[maxn];

Vector operator + (Vector a, Vector b){return Vector(a.x + b.x, a.y + b.y);}
Vector operator - (point a, point b){return Vector(a.x - b.x, a.y - b.y);}
Vector operator * (point a, double x){return Vector(a.x * x, a.y * x);}
double dot(Vector a, Vector b){return a.x * b.x + a.y * b.y;}
double cross(Vector a, Vector b){return a.x * b.y - a.y * b.x;}
point getD(point p, Vector v, point q, Vector w){
    Vector u = p - q;
    double t = cross(w, u) / cross(v, w);
    return p + v * t;
}
bool onSeg(point p, point a, point b){return dcmp(cross(p - a, p - b)) == 0 && dcmp(dot(p - a, p - b)) <= 0;}
bool check(point a1, point b1, point a2, point b2){
    if (onSeg(a1, a2, b2) || onSeg(b1, a2, b2) || onSeg(a2, a1, b1) || onSeg(b2, a1, b1)) return true;
    double c1 = cross(b1 - a1, a2 - a1), c2 = cross(b1 - a1, b2 - a1);
    double c3 = cross(b2 - a2, a1 - a2), c4 = cross(b2 - a2, b1 - a2);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}
void join(int x, int y){x = find(x), y = find(y); pre[y] = x;}

int main(){
    while (cin >> n){
        for (int i = 0; i <= n; i++) pre[i] = i;
        for (int i = 1; i <= n; i++){
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            line[i][0] = point(x1, y1);
            line[i][1] = point(x2, y2);
        }
        for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++){
            // if (dcmp(cross(line[i][0] - line[i][1], line[j][0] - line[j][1])) == 0){
            //     int flag = 0;
            //     if (onSeg(line[i][0], line[j][0], line[j][1]) || onSeg(line[i][1], line[j][0], line[j][1])) flag = 1;
            //     if (onSeg(line[j][0], line[i][0], line[i][1]) || onSeg(line[j][1], line[i][0], line[i][1])) flag = 1;
            //     if (flag) join(i, j);
            // }
            // else{
            //     point c = getD(line[i][0], line[i][1] - line[i][0], line[j][0], line[j][1] - line[j][0]);
            //     if (onSeg(c, line[i][0], line[i][1]) && onSeg(c, line[j][0], line[j][1])) join(i, j);
            // }
            if (check(line[i][0], line[i][1], line[j][0], line[j][1])) join(i, j);
        }
        int x, y;
        while (cin >> x >> y && x && y){
            cout << (find(x) == find(y) ? "CONNECTED" : "NOT CONNECTED") << endl;
        }
    }
    return 0;
}