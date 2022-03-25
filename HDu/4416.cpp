#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

ll ans[maxn << 1];

namespace sam{
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26], tot, last;
    void init(){ ms(ans, -1); ms(ch, 0); tot = last = 1; }
    void insert(int c){
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
    }
    
    int c[maxn << 1], a[maxn << 1];
    void rsort(){
        for (int i = 0; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
    }
}
using namespace sam;

char s[maxn];
int n, dep[maxn << 1];

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d%s", &n, s);
        init(); ms(dep, 0);
        for (int i = 0; s[i]; i++) insert(s[i] - 'a');
        while (n--){
            scanf("%s", s);
            int now = 1, l = 0;
            for (int i = 0; s[i]; i++){
                int c = s[i] - 'a';
                if (ch[now][c]) l++, now = ch[now][c], dep[now] = max(dep[now], l);
                else {
                    while (now && !ch[now][c]) now = link[now];
                    if (!now) now = 1, l = 0;
                    else l = len[now] + 1, now = ch[now][c], dep[now] = max(dep[now], l);
                }
            }
        }
        rsort(); ll ans = 0;
        for (int i = tot; i; i--){
            int now = a[i];
            if (dep[now]){
                dep[link[now]] = max(dep[link[now]], dep[now]);
                if (dep[now] < len[now]) ans += len[now] - dep[now];
            }
            else ans += len[now] - len[link[now]];
        }
        printf("Case %d: %lld\n", ++kase, ans);
    }
    return 0;
}