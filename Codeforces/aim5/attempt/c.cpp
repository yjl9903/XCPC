#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 132674 + 5;

struct node{
    int x1, y1, x2, y2;
}a[maxn];
bool cmp(node& a, node& b){
    if (a.x2 != b.x2) return a.x2 < b.x2;
    if (a.y2 != b.y2) return a.y2 < b.y2;
    if (a.x1 != b.x1) return a.x1 < b.x1;
    return a.y1 < b.y2;
}
int n;

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d%d%d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
    sort(a, a + n, cmp);
    for (int i = 0; i < n; i++){
        int c = 0, x = a[i].x1, y = a[i].y1;
        for (int i = 0; i < n; i++) 
            if (a[i].x1 <= x && x <= a[i].x2 && a[i].y1 <= y && y <= a[i].y2)
                c++;
        if (c >= n - 1) {
            printf("%d %d", x, y); return 0;
        }
        c = 0, x = a[i].x1, y = a[i].y2;
        for (int i = 0; i < n; i++) 
            if (a[i].x1 <= x && x <= a[i].x2 && a[i].y1 <= y && y <= a[i].y2)
                c++;
        if (c >= n - 1) {
            printf("%d %d", x, y); return 0;
        }
        c = 0, x = a[i].x2, y = a[i].y1;
        for (int i = 0; i < n; i++) 
            if (a[i].x1 <= x && x <= a[i].x2 && a[i].y1 <= y && y <= a[i].y2)
                c++;
        if (c >= n - 1) {
            printf("%d %d", x, y); return 0;
        }
        c = 0, x = a[i].x2, y = a[i].y2;
        for (int i = 0; i < n; i++) 
            if (a[i].x1 <= x && x <= a[i].x2 && a[i].y1 <= y && y <= a[i].y2)
                c++;
        if (c >= n - 1) {
            printf("%d %d", x, y); return 0;
        }
    }
    return 0;
}