#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <list>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

struct Node {
    int pre, nxt, val;
} a[maxn];

int n, m, v[maxn], mp[maxn], sz = 2;

int main() {
    a[1].pre = 0;
    a[1].nxt = 2;
    a[2].pre = 1;
    a[2].nxt = 0;
    int st = 1, ed = 2;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", v + i);
        int id = ++sz;
        mp[v[i]] = id;
        a[id].val = v[i];
        a[id].pre = a[ed].pre;
        a[id].nxt = ed;
        a[a[ed].pre].nxt = id;
        a[ed].pre = id;
    }
    int x;
    while (m--) {
        scanf("%d", &x);
        int id = mp[x];
        a[a[id].pre].nxt = a[id].nxt;
        a[a[id].nxt].pre = a[id].pre;
        a[id].nxt = a[st].nxt;
        a[id].pre = st;
        a[a[st].nxt].pre = id;
        a[st].nxt = id;
    }
    int u = 1;
    for (int i = 1; i <= n; i++) {
        u = a[u].nxt;
        printf("%d ", a[u].val);
    }
    return 0;
}