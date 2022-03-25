#include <cstdio>
#include <cstring>
#include <list>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m, p, s, a[maxn], nxt[maxn] = {0};

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) a[i] = i, nxt[i - 1] = i; 
    
    while (m--){
        scanf("%d%d", &p, &s);
        if (p == 1) continue;
        int k = 0, i = 0;
        while (k < p) i = nxt[i], k++;
        int op = i;
        while (k < p + s - 1) i = nxt[i], k++;
        int ed = i;
        nxt[nxt[0]] = nxt[ed];
        nxt[ed] = nxt[0];
        nxt[0] = op;
    }
    int i = nxt[0]; printf("%d", i); i = nxt[i]; 
    while (i){
        printf(" %d", i); i = nxt[i];
    }
    return 0;
}