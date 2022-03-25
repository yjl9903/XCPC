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
const int maxn = 100000 + 5;

int n, a[maxn];
vector<PII> ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    vector<int> v, v2;
    for (int i = 1; i <= n; i++) if (a[i] == 1) v.push_back(i); else v2.push_back(i);
    int len = 0;
    for (int i = 1; i < (int)v2.size(); i++) {
        len++;
        ans.push_back({v2[i - 1], v2[i]});
        a[v2[i - 1]]--; a[v2[i]]--;
    }
    if (!v.empty()) {
        if (v2.empty()) return puts("NO"), 0;
        len++;
        ans.push_back({v.back(), v2.front()});
        v.pop_back(); a[v2.front()]--;
        if (a[v2.front()] < 0) return puts("NO"), 0;
    }
    if (!v.empty()) {
        if (v2.empty()) return puts("NO"), 0;
        len++;
        ans.push_back({v2.back(), v.back()});
        v.pop_back(); a[v2.back()]--;
        if (a[v2.back()] < 0) return puts("NO"), 0;
    }
    for (int& x: v) {
        int flag = 1;
        for (int& y: v2) {
            if (!a[y]) continue;
            ans.push_back({x, y}); a[y]--;
            flag = 0;
            break;
        }
        if (flag) return puts("NO"), 0;
    }
    if ((int)ans.size() < n - 1) return puts("NO"), 0;
    cout << "YES " << len << endl;
    cout << (int)ans.size() << endl;
    for (auto& x: ans) printf("%d %d\n", x.first, x.second);
    return 0;
}