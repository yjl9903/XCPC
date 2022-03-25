#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct que{int l, r;}ope[maxn];
bool cmp(que a, que b){
    if (a.r == b.r) return a.l < b.l;
    return a.r < b.r;
}
int a[maxn], n, m, pre[maxn];
set<int> s;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) pre[i] = i;
        for (int i = 0; i < m; i++){
            int l, r; scanf("%d%d", &l, &r);
            pre[r] = min(pre[r], l);
        }
        for (int i = n - 1; i > 0; i--) pre[i] = min(pre[i], pre[i + 1]);

        for (int i = 1; i <= n; i++) s.insert(i);
        int l = 1, r = 0;
        for (int i = 1; i <= n; i++){
            while (l < pre[i]){
                s.insert(a[l]); l++; 
            }
            a[i] = *s.begin();
            s.erase(a[i]);
        }

        for (int i = 1; i <= n; i++){
            if (i != 1) printf(" ");
            printf("%d", a[i]);
        }
        printf("\n");
    }
    return 0;
}