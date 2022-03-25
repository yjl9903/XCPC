#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

int n, r, a[maxn], vis[maxn], cnt[maxn];
vector<int> v;

int main(){
    scanf("%d%d", &n, &r);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i); cnt[i] = cnt[i - 1] + a[i];
        if (a[i]) v.push_back(i);
    }
    if (v.empty()) return puts("-1"), 0;
    if (v.front() > r) return puts("-1"), 0;
    if (n - v.back() + 1 > r) return puts("-1"), 0;
    int tot = 0, ans = 0;
    for (int i = 0; i < v.size(); i++){
        if (tot < v[i] - r) return puts("-1"), 0;
        int j = i, m = v[i] + r - 1;
        while (v[j] - r + 1 < m && j < v.size()) j++;

    }
    printf("%d", ans);
    return 0;
}