#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int len, n, pos[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &len, &n);
        for (int i = 0; i < n; scanf("%d", &pos[i++]));
        sort(pos, pos + n);
        int res = 0, c;
        for (int i = 0; i < n; i++)
            res = max(res, min(pos[i], len - pos[i]));
        printf("%d", res);
        for (int i = 0; i < n; i++)
            res = max(res, max(pos[i], len - pos[i]));
        printf(" %d\n", res);
    }
    return 0;
}