#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, q, a[maxn], b[maxn];
int pos[maxn], sz, num, l[maxn], r[maxn], block[maxn];

void build(){
    ms(block, 0);
    sz = sqrt(n); num = n / sz; if (n % sz) num++;
    for (int i = 1; i <= num; i++) l[i] = (i - 1) * sz, r[i] = i * sz;
    r[num] = n;
    for (int i = 1; i <= n; i++) pos[i] = (i - 1) / sz + 1;
}
void add(int x, int y){

}
int query(int x, int y){
    
}

int main(){
    while (~scanf("%d%d", &n, &q)){
        for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
        build();
        int x, y; char cmd[10];
        while (q--){
            scanf("%s%d%d", cmd, &x, &y);
            if (cmd[0] == 'q'){

            }
            else if (cmd[0] == 'a'){
                add(x, y);
            }
        }
    }
    return 0;
}