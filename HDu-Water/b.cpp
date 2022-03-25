#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, q, tree[26][maxn];
char s[maxn];

inline int lowbit(int x){return x & -x;}
inline void update(int t, int i){
    while (i <= n){
        tree[t][i]++;
        i += lowbit(i);
    }
}
inline int query(int t, int i){
    int s = 0;
    while (i > 0){
        s += tree[t][i];
        i -= lowbit(i);
    }
    return s;
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        ms(tree, 0);
        scanf("%d%d%s", &n, &q, s + 1);
        for (int i = 1; i <= n; i++) update(s[i] - 'A', i);
        printf("Case #%d:\n", ++kase);
        while (q--){
            int l, r, res = 0; scanf("%d%d", &l, &r);
            for (int i = 0; i < 26; i++){
                res = query(i, r) - query(i, l - 1);
                if (res != 0){
                    break;
                }
            }
            printf("%d\n", res);
        }
    }
    return 0;
}