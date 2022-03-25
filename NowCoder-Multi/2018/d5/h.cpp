#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 3000000 + 5;
const int maxm = 100000 + 5;

int n;

namespace sam{
    int len[maxn], link[maxn], ch[maxn][2], tot, last;
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

string s[maxm];
char ss[maxn];
bool vis[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        for (int i = 0; i < n; i++){
            scanf("%s", ss); s[i] = ss;
        }
        ll ans = 0;
        for (int i = 0; i < n; i++){
            ans += s[i].length(); init();
            for (int j = 0; j < s[i].length(); j++) insert(s[i][j] - 'a');

            int now = last; ms(vis, 0);
            while (now) vis[now] = 1, now = link[now];
            
            for (int j = 0; j < n; j++){
                if (i == j) continue;
                int now = 1, r = 0;
                for (int k = 0; k < s[j].length(); k++){
                    if (ch[now][s[j][k] - 'a']){
                        now = ch[now][s[j][k] - 'a'];
                        if (vis[now]){
                            r = k + 1;
                        }
                    }
                    else break;
                }
                ans += r;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}