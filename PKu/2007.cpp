#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

struct point{
    int x, y;
    point(int x = 0, int y = 0): x(x), y(y){};
}p[maxn];

int cross(const point& a, const point& b){
    return a.x * b.y - a.y * b.x;
}
bool cmp(const point& a, const point& b){
    return cross(a, b) > 0;
}

int main(){
    int u, v, i = 1; cin >> p[0].x >> p[0].y;
    while (cin >> u >> v){
        p[i].x = u - p[0].x;
        p[i].y = v - p[0].y;
        i++;
    }
    sort(p + 1, p + i, cmp);
    cout << '(' << p[0].x << ',' << p[0].y << ')' << endl;
    for (int j = 1; j < i; j++){
        cout << '(' << p[j].x + p[0].x << ',' << p[j].y + p[0].y << ')' << endl;
    }
    return 0;
}