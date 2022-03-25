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
const int maxn = 100000 + 5;

int n, a[maxn];
map<int,int> mp;
vector<int> ans;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    ans.push_back(a[0]); ans.push_back(a[1]);
    for (int i = 2; i < n; i++) {
        int mn = 2e9 + 7, p = -1, sz = (int)ans.size();
        for (int j = 0; j < ans.size(); j++) {
            if (abs(a[i] - ans[(j + sz - 1) % sz]) + abs(a[i] - ans[j]) <= mn) {
                mn = abs(a[i] - ans[(j + sz - 1) % sz]) + abs(a[i] - ans[j]);
                p = j;
            }
        }
        vector<int> v;
        for (int i = 0; i < p; i++) v.push_back(ans[i]);
        v.push_back(a[i]);
        for (int i = p; i < sz; i++) v.push_back(ans[i]);
        ans = v;
    }
    for (int& x: ans) printf("%d ", x);
    return 0;
}