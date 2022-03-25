#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10 + 5;

int n, m, k, a[maxn], b[maxn], r1, r2;

void dfs(int p, int c){
    int x = 0;
    for (int i = 0; i < m; i++) x = x * 10 + a[i];
    r1 = min(r1, x); r2 = max(r2, x);
    if (p == m) return;
    if (c == k) return;
    dfs(p + 1, c);
    for (int i = p + 1; i < m; i++){
        if (a[p] == a[i]) continue;
        swap(a[p], a[i]); 
        dfs(p + 1, c + 1);
        swap(a[p], a[i]);
    }
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &k);
        int x = n; m = 0;
        while (x){
            a[m++] = x % 10;
            x /= 10;
        }
        reverse(a, a + m);
        if (m == 10) {
            puts("1000000000 1000000000");
            continue;
        }
        r1 = n; r2 = n;
        dfs(1, 0);
        for (int i = 1; i < m; i++){
            if (a[0] == a[i] || a[i] == 0) continue;
            swap(a[0], a[i]); 
            dfs(1, 1);
            swap(a[0], a[i]);
        }
        printf("%d %d\n", r1, r2);
    }
    return 0;
}