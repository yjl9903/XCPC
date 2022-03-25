#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

struct DS {
    int bag[maxn], cnt[maxn], mx = 0;
    void insert(int x, int t) {
        cnt[bag[x]]--;
        bag[x] += t;
        cnt[bag[x]]++;
        if (bag[x] == mx + 1) mx++;
        if (cnt[mx] == 0) mx--;
    }
} f;

int n, m;
PII a[maxn];
vector<int> bag[maxn];
map<int,int> mp;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
        if (a[i].first > a[i].second) swap(a[i].first, a[i].second);
        bag[a[i].first].push_back(i);
        f.insert(a[i].second, 1);
        if (a[i].first != a[i].second) {
            bag[a[i].second].push_back(i);
            f.insert(a[i].first, 1);
        }
    }
    int fl = 0;
    for (int i = 1; i <= n; i++) {
        for (auto& x: bag[i]) {
            f.insert(a[x].second, -1);
            if (a[x].first != a[x].second) f.insert(a[x].first, -1);
        }
        if ((int)bag[i].size() + f.mx >= m) {
            fl = 1; break;
        }
        for (auto& x: bag[i]) {
            f.insert(a[x].second, 1);
            if (a[x].first != a[x].second) f.insert(a[x].first, 1);
        }
    }
    if (fl) puts("YES");
    else puts("NO");
    return 0;
}