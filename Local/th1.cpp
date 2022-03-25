#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1030 + 5;

int n;
int tree[maxn][maxn] = {0};

inline int lowbit(int x){return x & -x;}
void update(int i, int j, int x){
    int k = j;
    while (i <= n){
        j = k;
        while (j <= n){
            tree[i][j] += x;
            j += lowbit(j);
        }
        i += lowbit(i);
    }
}
int query(int i, int j){
    int s = 0, k = j;
    while (i > 0){
        j = k;
        while (j > 0){
            s += tree[i][j];
            j -= lowbit(j);
        }
        i -= lowbit(i);
    }
    return s;
}

int main(){
    scanf("%*d%d", &n);
    int cmd, x, y, a, b;
    while (scanf("%d", &cmd)){
        if (cmd == 1){
            scanf("%d%d%d", &x, &y, &a); x++; y++;
            update(x, y, a);
        }
        else if (cmd == 2){
            scanf("%d%d%d%d", &x, &y, &a, &b); x++; y++; a++; b++;
            int ans = query(x - 1, y - 1) + query(a, b) - query(x - 1, b) - query(a, y - 1);
            printf("%d\n", ans);
        }
        else if (cmd == 3){
            return 0;
        }
    }
    return 0;
}