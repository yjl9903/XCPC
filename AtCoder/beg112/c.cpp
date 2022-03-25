#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

struct node{
    int x, y, h;
}a[maxn];
bool cmp(node a, node b){
    return a.h > b.h;
}
int n;

int main(){
    scanf("%d", &n); 
    for (int i = 0; i < n; i++) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].h);
    sort(a, a + n, cmp);
    for (int i = 0; i <= 100; i++) for (int j = 0; j <= 100; j++){
        int h = a[0].h + abs(i - a[0].x) + abs(j - a[0].y);
        int flag = 1;
        for (int k = 1; k < n; k++){
            int t = max(0, h - abs(i - a[k].x) - abs(j - a[k].y));
            if (t != a[k].h){
                flag = 0; break;
            }
        }
        if (flag){
            printf("%d %d %d", i, j, h); return 0;
        }
    }
    return 0;
}