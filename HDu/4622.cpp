#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 4000 + 5;

namespace sam{
    int len[maxn], link[maxn], ch[maxn][26], tot, last;
    ll cnt = 0;
    void init(){
        ms(ch, 0);
        tot = last = 1; cnt = 0;
    }
    ll insert(int c){
        int cur = ++tot, p = last;
        len[cur] = len[last] + 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; len[nq] = len[p] + 1;
                link[nq] = link[q]; link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        } 
        last = cur;
        return cnt = cnt + len[cur] - len[link[cur]];
    }
}
using namespace sam;

char s[maxn];
ll ans[maxn >> 1][maxn >> 1];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s", s);
        int len = strlen(s);
        for (int i = 0; i < len; i++){
            init();
            for (int j = i; j < len; j++){
                ans[i][j] = insert(s[j] - 'a');
            }
        }
        int q, l, r; scanf("%d", &q);
        while (q--){
            scanf("%d%d", &l, &r);
            printf("%lld\n", ans[l - 1][r - 1]);
        }
    }
    return 0;
}