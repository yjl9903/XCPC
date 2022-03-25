#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 5000 + 5;

struct point{
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y){}
    point operator + (const point& b){return point(x + b.x, y + b.y);}
    point operator - (const point& b){return point(x - b.x, y - b.y);}
    point operator * (double p){return point(x * p, y * p);}
}ul, rd, u[maxn], d[maxn], p[maxn];
double dot(const point& a, const point& b){return a.x * b.x + a.y * b.y;}
double cross(const point& a, const point& b){return a.x * b.y - a.y * b.x;}
int n, m, cnt[maxn];

int find(double x, double y){
    if (cross(u[0] - d[0], point(x, y) - d[0]) > 0) return 0;
    if (cross(u[n - 1] - d[n - 1], point(x, y) - d[n - 1]) < 0) return n;
    int l = 0, r = n - 1;
    while (l <= r){
        int m = (l + r) / 2;
        if (cross(u[m] - d[m], point(x, y) - d[m]) > 0){
            r = m - 1;
        }
        else {
            l = m + 1;
        }
    }
    return l;
}

int main(){
    int kase = 0;
    while (cin >> n >> m && n && m){
        cin >> ul.x >> ul.y >> rd.x >> rd.y; 
        ms(cnt, 0);
        for (int i = 0; i < n; i++){
            cin >> u[i].x >> d[i].x;
            u[i].y = ul.y; d[i].y = rd.y;
        }
        for (int i = 0; i < m; i++){
            double x, y; cin >> x >> y;
            // cout << find(x, y) << endl;
            cnt[find(x, y)]++;
        }
        if (kase++) cout << endl;
        for (int i = 0; i <= n; i++){
            cout << i << ": " << cnt[i] << endl;
        }
    }
    return 0;
}