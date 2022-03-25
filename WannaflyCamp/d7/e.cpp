#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;

struct Mat {
    int a[3][3];
    Mat() {
        ms(a, 0);
    }
    inline void clear() {
        ms(a, 0);
    }
    inline Mat operator*(const Mat& b) const {
        Mat ans;
        for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
            ans.a[i][j] = 0;
            for (int k = 0; k < 3; k++)
                ans.a[i][j] = (ans.a[i][j] + 1ll * a[i][k] * b.a[k][j]) % mod;
        }
        return ans;
    }
    inline int get() {
        int sum = 0;
        for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
            sum += a[i][j];
            if (sum >= mod) sum -= mod;
        }
        return sum;
    }
    bool empty() {
        int flag = 1;
        for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (a[i][j]) { flag = 0; break; }
        return flag;
    }
    void print() {
        for (int i = 0; i < 3; i++, puts("")) for (int j = 0; j < 3; j++, putchar(' ')) printf("%d", a[i][j]);
    }
} a[maxn], mul[maxn << 2], tag[maxn << 2];
Mat qpow(Mat x, int n) {
    Mat ans; ms(ans.a, 0);
    ans.a[0][0] = ans.a[1][1] = ans.a[2][2] = 1;
    while (n > 0) {
        if (n & 1) ans = ans * x;
        n >>= 1; x = x * x;
    }
    return ans;
}

int n, q;

inline void pushup(int rt) {
    mul[rt] = mul[rt << 1] * mul[rt << 1 | 1];
}
inline void pushdown(int rt, int ln, int rn) {
    if (tag[rt].empty()) return;
    mul[rt << 1] = qpow(tag[rt], ln);
    mul[rt << 1 | 1] = qpow(tag[rt], rn);
    tag[rt << 1] = tag[rt << 1 | 1] = tag[rt];
    tag[rt].clear();
}
inline void build(int l, int r, int rt) {
    if (l == r) {
        mul[rt] = a[l]; 
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
inline void update(int L, int R, Mat x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        mul[rt] = qpow(x, r - l + 1);
        tag[rt] = x;
        return ;
    }
    int m = (l + r) >> 1; pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
inline Mat query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        // dbg(l, r, rt);
        // mul[rt].print();
        return mul[rt];
    }
    int m = (l + r) >> 1; pushdown(rt, m - l + 1, r - m);
    Mat ans; ms(ans.a, 0);
    ans.a[0][0] = ans.a[1][1] = ans.a[2][2] = 1;
    if (L <= m) ans = ans * query(L, R, lson);
    if (R > m) ans = ans * query(L, R, rson);
    return ans;
}

int main(){
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < 3; j++) for (int k = 0; k < 3; k++) 
            scanf("%d", &a[i].a[j][k]);
    }
    build(1, n - 1, 1);
    int op, l, r;
    while (q--) {
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            Mat x;
            for (int j = 0; j < 3; j++) for (int k = 0; k < 3; k++) 
                scanf("%d", &x.a[j][k]);
            update(l, r, x, 1, n - 1, 1);
        } else if (op == 2) {
            printf("%d\n", query(l, r - 1, 1, n - 1, 1).get());
        }
    }
    return 0;
}