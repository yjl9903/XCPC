#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, a[maxn], pos[maxn];
set<int> s1, s2;
vector<PII> op;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (a[i] <= n / 2) s1.insert(i);
        else s2.insert(i);
    }
    for (int i = 1; i <= n / 2; i++) if (a[i] > n / 2) {
        auto it = s1.lower_bound(n / 2);
        if (it == s1.end()) break;
        if (i == 1) {
            op.push_back({1, *it});
            swap(a[1], a[*it]);
            s1.erase(*it);
            continue;
        }
        op.push_back({ i, n });
        op.push_back({ 1, *it });
        op.push_back({ 1, n });
        op.push_back({ i, n });
        op.push_back({ 1, *it });
        swap(a[i], a[*it]);
        s1.erase(it);
    }
    for (int i = 1; i <= n; i++) pos[a[i]] = i;
    for (int i = 1; i <= n / 2; i++) if (a[i] != i) {
        int p = pos[i];
        op.push_back({ p, n });
        op.push_back({ i, n });
        op.push_back({ p, n });
        swap(a[p], a[i]);
        pos[a[i]] = i; pos[a[p]] = p;
    }
    for (int i = n / 2 + 1; i <= n; i++) if (a[i] != i) {
        int p = pos[i];
        op.push_back({ 1, p });
        op.push_back({ 1, i });
        op.push_back({ 1, p});
        swap(a[p], a[i]);
        pos[a[p]] = p;
        pos[a[i]] = i;
    }
    // for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    // cout << endl;
    printf("%d\n", (int)op.size());
    for (auto& x: op) printf("%d %d\n", x.first, x.second);
    return 0;
}