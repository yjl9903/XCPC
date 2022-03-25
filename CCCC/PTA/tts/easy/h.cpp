#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 50 + 5;

int lc[maxn], rc[maxn];
int pre[maxn], in[maxn];

void build(int l1, int r1, int l2, int r2){
    if (l1 >= r1 || l2 >= r2)   return;
    if (l1 + 1 <= r1)
        lc[l1] = l1 + 1;
    int root = 0;
    for (int i = 0; i <= r2 - l2; i++)
        if (pre[l1] == in[i + l2])
            root = i;
    if (root && l1 + root + 1 <= r1)
        rc[l1] = l1 + root + 1;
    build(l1 + 1, l1 + root, l2, l2 + root - 1);
    build(l1 + root + 1, r1, l2 + root + 1, r2);
}

vector<int> ans;
void bfs(int p){
    queue<int> q; q.push(p);
    while (!q.empty()) {
        int t = q.front(); q.pop();
        ans.push_back(pre[t]);
        if (rc[t] != -1) q.push(rc[t]);
        if (lc[t] != -1) q.push(lc[t]);
    }
}

int n;

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", in + i);
    for (int i = 1; i <= n; i++) scanf("%d", pre + i);
    memset(lc, -1, sizeof lc);   
    memset(rc, -1, sizeof rc);
    build(1, n, 1, n);
    bfs(1);
    for (int i = 0; i < n; i++) {
        if (i > 0) putchar(' ');
        printf("%d", ans[i]);
    }
    return 0;
}