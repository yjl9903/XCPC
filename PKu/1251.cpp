#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

struct edge{char x, y; int d;};
bool cmp(const edge& a, const edge& b){
    return a.d < b.d;
}
vector<edge> v;

int n, pre[maxn];
void init(){
    for (int i = 0; i < maxn; i++) pre[i] = i;
}
int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}
void join(int x, int y){
    x = find(x), y = find(y);
    pre[x] = y;
}
int kruskal(){
    sort(v.begin(), v.end(), cmp);
    int ans = 0;
    for (int i = 0, a, b; i < v.size(); i++){
        a = find(v[i].x - 'A'), b = find(v[i].y - 'A');
        if (a == b) continue;
        join(a, b); ans += v[i].d;
    }   
    return ans;
}

int main(){
    while (~scanf("%d", &n) && n){
        char xx[2], yy[2]; int k; 
        v.clear(); init();
        for (int i = 2; i <= n; i++){
            scanf("%s%d", xx, &k);
            int c = 0;
            while (k--){
                scanf("%s%d", yy, &c);
                v.push_back({xx[0], yy[0], c});
            }
        }
        printf("%d\n", kruskal());
    }
    return 0;
}