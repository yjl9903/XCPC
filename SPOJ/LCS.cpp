#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 250000 + 5;

namespace sam{
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26], tot, last;
    void init(){ ms(ch, 0); tot = last = 1; }
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
}
using namespace sam;

char s[maxn];

int main(){
    scanf("%s", s);
    sam::init(); for (int i = 0; s[i]; i++) sam::insert(s[i] - 'a');
    scanf("%s", s);
    int ans = 0, now = 1, l = 0;
    for (int i = 0; s[i]; i++) {
        // if (ch[now][s[i] - 'a']) l++, now = ch[now][s[i] - 'a'];
        // else {
        //     while (now && !ch[now][s[i] - 'a']) now = link[now];
        //     if (!now) now = 1, l = 0;
        //     else l = len[now] + 1, now = ch[now][s[i] - 'a'];
        // }
        while (now && !ch[now][s[i] - 'a']) now = link[now], l = len[now];
        if (!now) now = 1, l = 0;
        else l++, now = ch[now][s[i] - 'a'];
        ans = max(ans, l);
    }
    printf("%d", ans);
    return 0;
}