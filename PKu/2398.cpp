#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 5000 + 5;
const int eps = 1e-6;

int dcmp(double x){if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;}
struct point{
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y){}
    point operator + (const point& b){return point(x + b.x, y + b.y);}
    point operator - (const point& b){return point(x - b.x, y - b.y);}
    point operator * (double p){return point(x * p, y * p);}
    bool operator < (const point& b) const {return dcmp(x - b.x) < 0 || (dcmp(x - b.x) == 0 && dcmp(y - b.y) < 0); }
}ul, rd, u[maxn], d[maxn], p[maxn];
double dot(const point& a, const point& b){return a.x * b.x + a.y * b.y;}
double cross(const point& a, const point& b){return a.x * b.y - a.y * b.x;}
int n, m, cnt[maxn], sum[maxn];

int find(double x, double y){
    if (x < ul.x || x > rd.x || y > ul.y || y < rd.y) return -1;
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
        ms(cnt, 0); ms(sum, 0);
        for (int i = 0; i < n; i++){
            cin >> u[i].x >> d[i].x; 
            u[i].y = ul.y; d[i].y = rd.y;
        }
        sort(u, u + n); sort(d, d + n);
        for (int i = 0; i < m; i++){
            double x, y; cin >> x >> y;
            // cout << find(x, y) << endl;
            cnt[find(x, y)]++;
            // int t = find(x, y);
            // if (t != -1) cout << i << ": " << t << endl;
        }
        // if (kase++) cout << endl;
        // for (int i = 0; i <= n; i++){
        //     cout << i << ": " << cnt[i] << endl;
        // }
        // sort(cnt, cnt + n + 1);
        for (int i = 0; i <= n; i++){
            sum[cnt[i]]++;
        }
        cout << "Box\n";
        for (int i = 1; i <= m; i++){
            if (sum[i]) cout << i << ": " << sum[i] << endl;
        }
    }
    return 0;
}