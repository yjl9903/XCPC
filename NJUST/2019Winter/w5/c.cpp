#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 2000000 + 5;

int n; char s[maxn], tmp[maxn];
string ss[maxn], tot; 
vector<int> pos[maxn];

int cnt[maxn << 2];
void pushup(int rt) {
    cnt[rt] = cnt[rt << 1] + cnt[rt << 1 | 1];
}
void update(int L, int R, int l, int r, int rt) {
    if (cnt[rt] == r - l + 1) return;
    if (l == r) {
        cnt[rt] = 1; s[l] = tot[l - L]; return;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    pushup(rt);
}

int main(){
    scanf("%d", &n);
    int len = 0;
    for (int i = 0, k; i < n; i++) {
        scanf("%s%d", tmp, &k);
        ss[i] = tmp;
        int m = strlen(tmp);
        for (int j = 0, p; j < k; j++) {
            scanf("%d", &p); p--;
            pos[i].push_back(p);
            len = max(len, p + m - 1);
        }
    }
    for (int i = 0; i < n; i++) {
        tot = ss[i];
        for (int j = 0; j < pos[i].size(); j++) {
            update(pos[i][j], pos[i][j] + ss[i].length() - 1, 0, len, 1);
        }
    }
    for (int i = 0; i < len; i++) if (!s[i]) s[i] = 'a';
    s[len + 1] = 0;
    cout << s << endl;
    return 0;
}