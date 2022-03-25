#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int query(int x1, int y1, int x2, int y2) {
    cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    int r = 0; cin >> r; return r;
}
void answer(int x1, int y1, int x2, int y2) {
    cout << "! " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
}

int n;

int main() {
    cin >> n;
    int l = -1, r = -1, d = -1, u = -1;
    for (int i = 1; i < n; i++) {
        int ans = query(1, 1, i, n);
        if (ans % 2) {
            if (u == -1) u = i;
            d = i + 1;
        }
    }
    for (int i = 1; i < n; i++) {
        int ans = query(1, 1, n, i);
        if (ans % 2) {
            if (l == -1) l = i;
            r = i + 1;
        }
    }
    dbg(l, r, d, u);
    int x1, y1, x2, y2;
    if (l == -1) {
        int x = 1, y = n, ans = 1;
        while (x <= y) {
            int m = (x + y) / 2;
            if (query(1, 1, u, m) % 2) y = m - 1, ans = m;
            else x = m + 1;
        }
        y1 = y2 = ans; x1 = u; x2 = d;
    } else if (d == -1) {
        int x = 1, y = n, ans = 1;
        while (x <= y) {
            int m = (x + y) / 2;
            if (query(1, 1, m, l) % 2) y = m - 1, ans = m;
            else x = m + 1;
        }
        x1 = x2 = ans; y1 = l; y2 = r;
    } else {
        if (query(d, l, d, l) == 1) {
            x1 = d; x2 = u; y1 = l; y2 = r;
        } else {
            x1 = d; x2 = u; y1 = r; y2 = l;
        }
    }
    answer(x1, y1, x2, y2);
    return 0;
}