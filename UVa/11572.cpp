#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int n, a[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d\n", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        set<int> s; int res = 0;
        for (int l = 1, r = 1; l <= n && r <= n; l++){
            while (r <= n && !s.count(a[r])) s.insert(a[r]), r++;
            // printf("%d %d\n", l, r);
            res = max(res, r - l);
            s.erase(a[l]);
        }
        printf("%d\n", res);
    }
    return 0;
}