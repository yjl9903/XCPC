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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

inline void add(int& x, int y) {
    x += y; if (x >= mod) x -= mod;
}
inline void sub(int& x, int y) {
    x -= y; if (x < 0) x += mod;
}

int n, a[maxn], pos[maxn];

inline int lowbit(int x) {
    return x & -x;
}
struct BIT {
    int a[maxn];
    inline void update(int i, int x) {
        for (; i <= n; i += lowbit(i)) add(a[i], x);
    }
    inline int query(int i) {
        int r = 0;
        for (; i > 0; i -= lowbit(i)) add(r, a[i]);
        return r;
    }
} f1, f2;

int main() {
    scanf("%d", &n);
    vector<int> lsh;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        lsh.push_back(a[i]);
    }
    sort(lsh.begin(), lsh.end());
    for (int i = 1; i <= n; i++) {
        int rk = lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1;
        pos[rk] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        f1.update(pos[i], pos[i]);
        f2.update(pos[i], n - pos[i] + 1);
        int x = 1ll * (n - pos[i] + 1) * f1.query(pos[i]) % mod;
        int y = 1ll * pos[i] * ((f2.query(n) - f2.query(pos[i] - 1) + mod) % mod) % mod;
        int z = 1ll * pos[i] * (n - pos[i] + 1) % mod;
        add(ans, 1ll * x * lsh[i - 1] % mod); 
        add(ans, 1ll * y * lsh[i - 1] % mod); 
        sub(ans, 1ll * z * lsh[i - 1] % mod);
    }
    cout << ans << endl;
    return 0;
}