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
const int maxn = 1000 + 5;

int n, m, a[maxn][maxn], ans[maxn][maxn];
vector<int> row[maxn], col[maxn];

void init(vector<int>& v) {
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
}
int gid(int x, vector<int>& v) {
    return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        scanf("%d", &a[i][j]);
        row[i].push_back(a[i][j]);
        col[j].push_back(a[i][j]);
    }
    for (int i = 1; i <= n; i++) init(row[i]);
    for (int i = 1; i <= m; i++) init(col[i]);
    for (int i = 1; i <= n; i++, puts("")) for (int j = 1; j <= m; j++) {
        int x = gid(a[i][j], row[i]);
        int y = gid(a[i][j], col[j]);
        printf("%d ", 1 + max(x - 1, y - 1) + max((int)row[i].size() - x, (int)col[j].size() - y));
    }
    return 0;
}