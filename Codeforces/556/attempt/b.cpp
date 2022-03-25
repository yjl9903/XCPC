#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, q, nxt[maxn][26];
char s[maxn];

struct node {
    int pos, ch, nxt;
};
vector<node> v[3];

int main() {
    scanf("%d%d%s", &n, &q, s + 1);
    for (int i = 0; i < 26; i++) nxt[n][i] = -1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            nxt[i][j] = nxt[i + 1][j];
        }
        nxt[i][s[i + 1] - 'a'] = i + 1;
    }
    v[0].push_back({0, -1, -1});
    v[1].push_back({0, -1, -1});
    v[2].push_back({0, -1, -1});
    char op[2], ch[2]; int tp;
    while (q--) {
        scanf("%s%d", op, &tp); tp--;
        int flag = 0;
        if (op[0] == '+') {
            scanf("%s", ch);
            node ed = v[tp].back();
            int pos = ed.pos;
            if (pos == -1 || nxt[pos][ch[0] - 'a'] == -1) {
                flag = 1;
                v[tp].push_back({-1, ch[0] - 'a', -1});
            } else {
                int nx = nxt[pos][ch[0] - 'a'], nxp = nx;
                if (nx != -1) nx = nxt[nx][ch[0] - 'a'];
                v[tp].push_back({nxp, ch[0] - 'a', nx});
                nxt[pos][ch[0] - 'a'] = nx;
            }
        } else {

        }
        if (flag) puts("NO");
        else puts("YES");
    }
    return 0;
}