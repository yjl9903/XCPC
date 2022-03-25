#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
const int maxn = 100000 + 5;

int pre[maxn], val[maxn], n, k, ans;
void init(){ for (int i = 0; i < maxn; i++) pre[i] = i, val[i] = 0; }
int find(int x){ 
    if (x == pre[x]) return x;
    int t = find(pre[x]);
    val[x] = (val[x] + val[pre[x]]) % 3;
    return pre[x] = t;
}
bool join(int x, int y, int t){ 
    int xx = find(x), yy = find(y);
    if (xx == yy){
        return (val[x] - val[y] + 3) % 3 == t;
    }
    pre[xx] = yy;
    val[xx] = (val[y] - val[x] + t + 6) % 3;
    return true;
}

int main(){
    scanf("%d%d", &n, &k); init();
    int op, x, y;
    while (k--){
        scanf("%d%d%d", &op, &x, &y);
        if (x > n || y > n) {ans++; continue;}
        if (op == 1){
            if (!join(x, y, 0)) ans++;
        }
        else if (op == 2){
            if (x == y) {ans++; continue;}
            if (!join(x, y, 1)) ans++;
        }
    }
    printf("%d", ans);
    return 0;
}