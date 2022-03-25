#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;

struct DSU {
    int pre[maxn];
    int find(int x) {
        return x == pre[x] ? x : pre[x] = find(pre[x]);
    }
    void join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return ;
        pre[x] = y;
    }
    int check(int x, int y) {
        return find(x) == find(y);
    }
    void init(int n) {
        for (int i = 1; i <= n; i++) pre[i] = i;
    }
} f1,f2;

void query(int u1, int v1, int u2, int v2) {
    cout << u1 << ' ' << v1 << ' ' << u2 << ' ' << v2 << endl;
    int x; cin >> x; 
    if (x) {
        f1.join(u1, v1);
        f2.join(u2, v2);
    } else {
        f1.join(u2, v2);
        f2.join(u1, v1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        f1.init(n); f2.init(n);
        query(1, 2, 3, 1);
        query(3, 4, 5, 3);
        if (f1.check(1, 4) || f2.check(1, 4)) query(4, 5, 2, 4);
        else query(4, 5, 2, 5);
        int flag = 0;
        for (int u1 = 1; u1 <= 5; u1++) {
            for (int v1 = u1 + 1; v1 <= 5; v1++) {
                for (int u2 = 1; u2 <= 5; u2++) {
                    for (int v2 = u2 + 1; v2 <= 5; v2++) {
                        if (f1.check(u1, v1) || f2.check(u1, v1)) continue;
                        if (f1.check(u2, v2) || f2.check(u2, v2)) continue;
                        if (u1 == u2 && v1 == v2) continue;
                        query(u1, v1, u2, v2); 
                        flag = 1;
                        break;
                    }
                    if (flag) break;
                }
                if (flag) break;
            }
            if (flag) break;
        }
        for (int i = 6; i <= n; i++) {
            query(1, i, 2, i);
        }
    }
    return 0;
}