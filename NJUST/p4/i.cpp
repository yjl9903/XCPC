#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20000 + 5;

struct point{
    int x, y;
    point(int x, int y): x(x), y(y){}
}m[maxn];
int N, M;

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &N, &M);
        for (int i = 0; i < N; i++)
            scanf("%d%d", &m[i].x, &m[i].y);
        while (M--){
            int x, y, D, W, res = 0; scanf("%d%d%d%d", &x, &y, &D, &W);
            
        }
    }
    return 0;
}