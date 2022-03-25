#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, n) for (int i = 1; i <= n; ++i)
#define iter_r(i, n) for (int i = n; i >= 1; --i)
#define forw(i, a, b) for (int i = a; i <= b; ++i)
 
#define lx x << 1
#define rx x << 1 | 1
#define RT 1, 1, n
#define SL lx, l, mid
#define SR rx, mid + 1, r
 
const int NR = 201000;
 
typedef pair<int, int> pii;
#define fi first
#define se second
 
int c[NR], sa[NR],rk[NR], ht[NR], st[20][NR], lg[NR];
int ta[NR], tb[NR];//, rk[NR], ht[NR];
int n, q;
char s[NR];
pii t[NR<<2];
 
void bsa(char *s) {
    int *x = ta, *y = tb, m = 1000;
 
    iter(i, n) ++c[x[i] = s[i]];
    iter(i, m) c[i] += c[i-1];
    iter_r(i, n) sa[c[x[i]]--] = i;
 
    for (int k = 1, p = 0; p < n; m = p, k <<= 1) {
        iter(i, m) c[i] = 0; c[0] = p = 0;
        forw(i, n-k+1, n) y[++p] = i;
        iter(i, n) if (sa[i] - k > 0) y[++p] = sa[i] - k;
        iter(i, n) ++c[x[y[i]]];
        iter(i, m) c[i] += c[i-1];
        iter_r(i, n) sa[c[x[y[i]]]--] = y[i];
 
        int i; for (i=2, p=1, y[sa[1]]=1; i <= n; ++i)
            y[sa[i]] = (x[sa[i]] == x[sa[i-1]] && x[sa[i]+k] == x[sa[i-1]+k]) ? p : ++p;
 
        swap(x, y);
    }
 
    iter(i, n) rk[sa[i]] = i;
    for (int i=1, j, k; i <= n; ++i) if (rk[i] < n) {
        j = sa[rk[i]+1];
        for (k = max(ht[rk[i-1]]-1, 0); s[i+k] == s[j+k]; ++k);
        ht[rk[i]] = k;
    }
}
 
int next_less(int x, int l, int r, int p, int w) {
    //fprintf(stderr, "%d %d %d %d\n",l,r,t[x].fi,w);
    if (t[x].fi >= w) return -1;
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (p <= mid) {
        int tmp = next_less(SL, p, w);
        return tmp != -1 ? tmp : next_less(SR, p, w);
    } else return next_less(SR, p, w);
}
 
int lcp(int i, int j) {
    if (i == j) return n-i+1;
    int l=rk[i], r=rk[j];
    if (l > r) swap(l, r);
    r--;
    int k = lg[r-l+1];
    //fprintf(stderr, "%d %d %d %d\n",l,r,k,);
    return min(st[k][l], st[k][r-(1<<k)+1]);
}
 
pii query(int x, int l, int r, int L, int R) {
    if (L <= l && r <= R) return t[x];
    int mid=(l+r)/2; pii tmp=pii(1e9, 0);
    if (L <= mid) tmp=min(tmp, query(SL, L, R));
    if (R > mid) tmp=min(tmp, query(SR, L, R));
    return tmp;
}
 
pii query(int l, int r, int k) {
    if (l == r) return pii(l, r);
    if (k == 1) return pii(l, r);
    int np = next_less(RT, l, rk[l]);
    //fprintf(stderr, "%d %d %d\n", np,r,l);
    if (np > r || np == -1) np = query(RT, l+1, r).se;
    int per = np - l, tmp = min(lcp(l, np), r-np+1), len = tmp/per*per;
 
    //fprintf(stderr,"!%d %d\n", np, len);
     
    if (np + len <= r && rk[np + len] > rk[l]) return pii(l, r);
    int cnt = tmp/per+1;
    //fprintf(stderr, "%d %d\n", cnt,l + cnt / k * (k-1) * per);
    if (np + len <= r) {
        if (cnt % k == 0) return pii(l + cnt / k * (k-1) * per, r);
        else ++cnt;
    }
    return pii(l, l + ((cnt + k - 1) / k) * per - 1);
}
 
void build(int x, int l, int r) {
    if (l == r) { t[x] = pii(rk[l], l); return; }
    int mid = (l+r)/2;
    build(SL); build(SR);
    t[x] = min(t[lx], t[rx]);
}
 
 
 
int main() {
//  freopen("in.txt", "r", stdin);
//  freopen("out.txt", "w", stdout);
    scanf("%s%d", s + 1, &q); n=strlen(s+1);
    bsa(s); build(RT);
    iter(i, n) st[0][i] = ht[i], lg[i] = lg[i-1] + ((1<<(lg[i-1]+1)) == i);
    for (int k=1; (1<<k) <= n-1; ++k)
        for (int i=1; i+(1<<k)-1<=n-1;++i)
            st[k][i]=min(st[k-1][i], st[k-1][i+(1<<(k-1))]);
    //iter(i ,n)printf("%d ", rk[i]);
    iter(i, q) {
        int l, k;
        scanf("%d%d", &l, &k);
        pii tr = query(l, n, k);
        printf("%d %d\n", tr.fi, tr.se);
        //if (i%100==0) fprintf(stderr, "%d\n",i);
     
    }
    return 0;
}