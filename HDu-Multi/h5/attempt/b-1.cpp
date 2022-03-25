#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int n, m, k, a[maxn], b[maxn];

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
        // for (int i = 0; i < m; i++) printf("%d", a[i]);
        // puts("");
        memcpy(b, a, sizeof a);
        sort(b, b + m);
        int r1 = n, r2 = n;
        do{
            int c = 0, x = 0;
            for (int i = 0; i < m; i++) {
                if (a[i] != b[i]) c++;
                x = x * 10 + b[i];
            }
            int d = c / 2 + c % 2;
            printf("%d %d\n", x, c);
            if (d <= k){
                r1 = min(r1, x); r2 = max(r2, x);
            }
        } while(next_permutation(b, b + m));
        printf("%d %d\n", r1, r2);
    }
    return 0;
}