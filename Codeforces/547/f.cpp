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
const int maxn = 2000 + 5;
const int inf = 5e6;

int n, a[maxn], sum, mx = -inf;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    map< int,vector<PII> > mp;
    for (int i = 1; i <= n; i++) {
        int tot = 0;
        for (int j = i; j <= n; j++) {
            tot += a[j];
            mp[tot].push_back({i, j});
        }
    }
    int ans = 0, p = 0;
    for (auto& x: mp) {
        auto v = x.second;
        sort(v.begin(), v.end(), [](PII a, PII b) {
            if (a.second == b.second) return a.first < b.first;
            return a.second < b.second;
        });
        int tot = 0, sz = (int)v.size(), i = 0;
        while (i < sz) {
            tot++; int j = i;
            while (j < sz && v[j].first <= v[i].second) j++;
            i = j;
        }
        if (tot > ans) ans = tot, p = x.first;
    }
    printf("%d\n", ans);
    auto v = mp[p];
    sort(v.begin(), v.end(), [](PII a, PII b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second < b.second;
    });
    int sz = (int)v.size(), i = 0;
    while (i < sz) {
        printf("%d %d\n", v[i].first, v[i].second);
        int j = i;
        while (j < sz && v[j].first <= v[i].second) j++;
        i = j;
    }
    return 0;
}