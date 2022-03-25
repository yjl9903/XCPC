#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 132674 + 5;
const int inf = 1 << 30;

struct rect{
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    rect(){x1 = -inf; y1 = -inf; x2 = inf; y2 = inf;}
    rect(int a, int b, int c, int d):x1(a), y1(b), x2(c), y2(d){}
    rect operator + (const rect& b) const{
        return rect(max(x1, b.x1), max(y1, b.y1), min(x2, b.x2), min(y2, b.y2));
    }
}a[maxn], pre[maxn], suf[maxn];

int n;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d%d%d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
    for (int i = n; i >= 1; i--) suf[i] = suf[i + 1] + a[i];
    for (int i = 1; i <= n; i++){
        rect tmp = pre[i - 1] + suf[i + 1];
        // printf("%d %d %d %d\n", tmp.x1, tmp.y1, tmp.x2, tmp.y2);
        if (tmp.x1 <= tmp.x2 && tmp.y1 <= tmp.y2) {
            printf("%d %d", tmp.x1, tmp.y1); return 0;
        }
    }
    return 0;
}