#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <bitset>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

struct fastIO {
    char s[100000]; int it,len;
    fastIO() { it = len = 0; }
    inline char get() {
        if (it < len) return s[it++];
        it = 0; len = fread(s, 1, 100000, stdin);
        if (len == 0) return EOF;
        else return s[it++];
    }
    bool notend() {
        char c = get();
        while(c == ' ' || c == '\n') c = get();
        if (it > 0) it--;
        return c != EOF;
    }
} buff;
inline int gi() {
    int r = 0; bool ng = 0;
    char c = buff.get();
    while (c != '-' && (c < '0' || c > '9')) c = buff.get();
    if (c == '-') ng = 1, c = buff.get();
    while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
    return ng ? -r : r;
}

struct Mat {
	static const int M = 51;
	ll a[M];
	void clear() {
		for (int i = 0; i < M; i++) a[i] = 0;
	}
	Mat() {
		clear();
	}
	void eye() {
		for (int i = 0; i < M; i++) a[i] = 1ll << i;
	}
	Mat operator * (const Mat& b) {
		Mat tmp, ans;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				if (b.a[i] & (1ll << j)) tmp.a[j] ^= (1ll << i);
			}
		}
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				if (a[i] & tmp.a[j]) ans.a[i] ^= (1ll << j);
			}
		}
		return ans;
	}
    void rebuild(ll mp) {
        clear();
        int last = 0;
        for (int i = 0; i <= M; i++) {
            bool flag = (mp >> i) & 1;
            if (i == M || !flag) {
                ll tot = 0;
                for (int p = last; p < i; p++) tot |= 1ll << p;
                for (int p = last; p < i; p++) a[p] |= tot;
                last = i + 1;
            }
        }
    }
	void print() const {
        #ifdef XLor
		for (int i = 0; i < M; i++) for (int j = 0; j < M; j++)
			printf("%d%c", (a[i] >> j) & 1, " \n"[j == M - 1]);
        #endif
	}
} a[maxn << 2], tmp;

int q;

ll mp[maxn << 2], ump;
void update(int L, int R, int l = 1, int r = 1e5, int rt = 1) {
    if ((ump & mp[rt]) == ump) return ;
    if (l == r) {
        mp[rt] |= ump; a[rt].rebuild(mp[rt]);
        return ;
    }
    int m = (l + r) / 2;
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    a[rt] = a[rt << 1] * a[rt << 1 | 1];
    mp[rt] = mp[rt << 1] & mp[rt << 1 | 1];
}
void query(int L, int R, int l = 1, int r = 1e5, int rt = 1) {
    if (L <= l && r <= R) {
        tmp = tmp * a[rt]; return ;
    }
    int m = (l + r) / 2;
    if (L <= m) query(L, R, lson);
    if (R > m) query(L, R, rson);
}

int main() {
    q = gi();
    int op, x1, y1, x2, y2;
    while (q--) {
        op = gi(); x1 = gi(); y1 = gi(); x2 = gi(); y2 = gi();
        if (op == 0) {
            ump = 0;
            for (int i = min(x1, x2); i <= max(x1, x2); i++) ump |= 1ll << i;
            update(min(y1, y2), max(y1, y2));
        } else if (op == 1) {
            if (y1 > y2) swap(y1, y2), swap(x1, x2);
            tmp.eye();
            query(y1, y2);
            ll ok = (tmp.a[x1] >> x2) & 1;
            if (ok) puts("1");
            else puts("0");
        }
    }
    return 0;
}