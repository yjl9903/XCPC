#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

namespace sam{
    int len[maxn], link[maxn], ch[maxn][26], tot, last, cnt[maxn];
    void init(){
        ms(ch, 0); ms(cnt, 0);
        tot = last = 1;
    }
    void insert(int c){
        int cur = ++tot, p = last;
        len[cur] = len[last] + 1; cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]){
                link[cur] = q;
            }
            else {
                int nq = ++tot; len[nq] = len[p] + 1;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                link[nq] = link[q]; link[cur] = link[q] = nq;
                while (ch[p][c] == q){
                    ch[p][c] = nq; 
                    p = link[p];
                }
            }
        }
        last = cur;
    }
    int c[maxn], a[maxn];
    void rsort(){
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
        for (int i = tot; i; i--){
            int p = a[i];
            cnt[link[p]] += cnt[p];
        }
    }
}

using namespace sam;

char s[maxn];

int main(){
    int a, b;
    while (~scanf("%s%d%d", s, &a, &b)){
        init();
        for (int i = 0; s[i]; i++) insert(s[i] - 'A');
        rsort();
        ll ans = 0;
        for (int i = 2; i <= tot; i++) if (cnt[i] >= a && cnt[i] <= b) ans += len[i] - len[link[i]];
        printf("%lld\n", ans);
    }
    return 0;
}