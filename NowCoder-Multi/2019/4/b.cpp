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
const int maxl = 33;

struct LinearBase {
    ll a[maxl + 5];
    int cnt;
    LinearBase() { cnt = 0; ms(a, 0); }
    void clear() { cnt = 0; ms(a, 0); }
    void insert(ll x) {
        for (int i = maxl - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (a[i]) x ^= a[i];
                else {
                    for (int k = 0; k < i; k++) 
                        if (x & (1ll << k)) x ^= a[k];
                    for (int k = i + 1; k < maxl; k++) 
                        if (a[k] & (1ll << i)) a[k] ^= x;
                    a[i] = x; cnt++;
                    return ;
                }
            }
        }
    }
    bool check(ll x) {
        for (int i = maxl - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (a[i]) x ^= a[i];
                else return false;
            }
        }
        return true;
    }
    void read() {
        int k; ll x; scanf("%d", &k);
        while (k--) {
            scanf("%lld", &x); insert(x);
        }
    }
} a[maxn << 2];

LinearBase intersect(const LinearBase& A, const LinearBase& B) {
	LinearBase all, C, D;
	for (int i = maxl - 1; i >= 0; i--) {
		all.a[i] = A.a[i];
		D.a[i] = 1ll << i;
	}
	for (int i = maxl - 1; i >= 0; i--) {
		if (B.a[i]) {
			ll v = B.a[i], k = 0;
			bool can = true;
			for (int j = 60; j >= 0; j--) {
				if (v & (1ll << j)) {
					if (all.a[j]) {
						v ^= all.a[j];
						k ^= D.a[j];
					} else {
						can = false;
						all.a[j] = v;
						D.a[j] = k;
						break;
					}
				}
			}

			if (can) {
				ll v = 0;
				for (int j = 60; j >= 0; j--) {
					if (k & (1ll << j)) {
						v ^= A.a[j];
					}
				}
				C.insert(v);
			}
		}
	}
	return C;
}

int n, q;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
void build(int l, int r, int rt) {
    if (l == r) {
        a[rt].read();
        return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    a[rt] = intersect(a[rt << 1], a[rt << 1 | 1]);
}
int query(int L, int R, ll x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) return a[rt].check(x);
    int m = (l + r) / 2;
    if (L <= m && !query(L, R, x, lson)) return false;
    if (R > m && !query(L, R, x, rson)) return false;
    return true;
}

int main() {
    scanf("%d%d", &n, &q);
    build(1, n, 1);
    while (q--) {
        int l, r; ll x; scanf("%d%d%lld", &l, &r, &x);
        puts(query(l, r, x) ? "YES" : "NO");
    }
    return 0;
}