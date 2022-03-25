#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, res;
struct node{
    int x, y, tp;
    double ang;
    node(int xx, int yy, int tt): x(xx), y(yy), tp(tt){}
    node(){}
    bool operator<(const node& b){return ang < b.ang;}
}a[maxn];
int cross(node a, node b){return a.x * b.y - a.y * b.x;}
bool cmp(node a, node b){return cross(a, b) > 0;}

int main(){
    while (~scanf("%d", &n) && n){
        for (int i = 0; i < n; i++){
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].tp);
        }
        res = 0;
        if (n <= 2){printf("2\n"); continue;}
        for (int i = 0; i < n; i++){
            vector<node> v;
            for (int j = 0; j < n; j++) if (i != j){
                node x;
                if (a[j].tp == 0) x = node(a[i].x - a[j].x, a[i].y - a[j].y, 1);
                else x = node(a[j].x - a[i].x, a[j].y - a[i].y, 1);
                x.ang = atan2(x.y, x.x);
                v.push_back(x);
            }
            sort(v.begin(), v.end());
            int l = 0, r = 0, cnt = 2;
            while (l < v.size()){
                if (r == l) r = (r + 1) % v.size(), cnt++;
                while (r != l && cross(v[l], v[r]) >= 0) r = (r + 1) % v.size(), cnt++;
                cnt--; l++;
                res = max(res, cnt);
            }
            
        }
        printf("%d\n", res);
    }
    return 0;
}