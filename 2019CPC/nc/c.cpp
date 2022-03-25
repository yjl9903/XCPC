#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 25;
const int maxn = 200000 + 5;

struct Mat {
    static const int M = 5;
    int a[M][M];
    void clear() { 
        for (int i = 0; i < M; i++) 
            for (int j = 0; j < M; j++)
                a[i][j] = inf;
    }
    Mat() { clear(); }
    void eye() { for (int i = 0; i < M; i++) a[i][i] = 1; }
    int* operator [] (int x) { return a[x]; }
    const int* operator [] (int x) const { return a[x]; }
    Mat operator * (const Mat& b) {
        const Mat& a = *this; Mat r;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                for (int k = 0; k < M; k++)
                    r[i][j] = min(r[i][j], a[i][k] + b[k][j]);
        return r;
    }
} tr[maxn << 2], ans;

int n, q;
char s[maxn];

void build(int l, int r, int rt) {
    tr[rt].clear();
    if (l == r) {
        for(int i = 0; i < 5; i++) tr[rt][i][i] = 0;
        if(s[l] == '2') tr[rt][0][0] = 1, tr[rt][0][1] = 0;
        if(s[l] == '0') tr[rt][1][1] = 1, tr[rt][1][2] = 0;
        if(s[l] == '1') tr[rt][2][2] = 1, tr[rt][2][3] = 0;
        if(s[l] == '9') tr[rt][3][3] = 1, tr[rt][3][4] = 0;
        if(s[l] == '8') tr[rt][3][3] = 1, tr[rt][4][4] = 1;
        return ;
    }
    int m = (l + r) / 2;
    build(rson); build(lson);
    tr[rt] = tr[rt << 1 | 1] * tr[rt << 1];
}
Mat query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return tr[rt];
    int m = (l + r) / 2;
    if(R <= m) return query(L, R, lson);
    if(m < L) return query(L, R, rson);
    return query(L, R, rson) * query(L, R, lson);
}

int main() {
    scanf("%d%d%s", &n, &q, s + 1);
    build(1, n, 1);
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        Mat ans = query(l, r, 1, n, 1);
        if (ans[0][4] > n) puts("-1");
        else printf("%d\n", ans[0][4]);
    }
    return 0;
}