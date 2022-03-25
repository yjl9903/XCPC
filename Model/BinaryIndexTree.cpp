// HDu1166 

#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 50000 + 5;

int bit[maxn], n, m;

inline int lowbit(int x) { return x & -x; }
void add(int i, int x){
    while (i <= n)
    {
        bit[i] += x;
        i += lowbit(i);
    }
}
int getSum(int i)
{
    int s = 0;
    while (i > 0){
        s += bit[i];
        i -= lowbit(i);
    }
    return s;
}

int main(){
    int T, kase = 0;
    scanf("%d", &T);
    while (T--){
        ms(bit, 0);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++){
            int x;
            scanf("%d", &x);
            add(i, x);
        }
        char cmd[20];
        printf("Case %d:\n", ++kase);
        while (scanf("%s", cmd)){
            int x, y;
            if (cmd[0] == 'E') break;
            if (cmd[0] == 'Q'){
                scanf("%d%d", &x, &y);
                printf("%d\n", getSum(y) - getSum(x - 1));
            }
            if (cmd[0] == 'A'){
                scanf("%d%d", &x, &y);
                add(x, y);
            }
            if (cmd[0] == 'S'){
                scanf("%d%d", &x, &y);
                add(x, -y);
            }
        }
    }
    return 0;
}