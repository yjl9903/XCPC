#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct node {
    int val, a, b;
    bool operator<(const node& b) const {
        return val > b.val;
    }
};

int n, a[maxn], b[maxn], last[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    priority_queue<node> pq; pq.push({a[1] + b[1], 1, 1});
    last[1] = 1;
    vector<int> v;
    int k = n;
    while (k--) {
        node tp = pq.top(); pq.pop();
        v.push_back(tp.val);
        if (last[tp.a] < n) {
            last[tp.a]++;
            pq.push({a[tp.a] + b[last[tp.a]], tp.a, last[tp.a]});
        }
        if (tp.a < n) {
            int aa = tp.a + 1;
            if (last[aa] >= n) continue;
            last[aa]++;
            pq.push({a[aa] + b[last[aa]], aa, last[aa]});
        }
    }
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) putchar(' ');
        printf("%d", v[i]);
    }
    return 0;
}