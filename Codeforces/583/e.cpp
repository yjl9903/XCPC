#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;
PII d[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i].first);
        d[i].second = 2 * i - 1;
    }
    sort(d + 1, d + 1 + n);
    reverse(d + 1, d + 1 + n);
    vector<PII> ans;
    vector<int> vec; vec.push_back(d[1].second);
    for (int i = 2; i <= n; i++) {
        ans.emplace_back(d[i - 1].second, d[i].second);
        vec.push_back(d[i].second);
    }
    for (int i = 1; i <= n; i++) {
        int pos = i + d[i].first - 2;
        if (pos == (int)vec.size() - 1) {
            ans.emplace_back(vec[pos], d[i].second + 1);
            vec.push_back(d[i].second + 1);
        } else {
            ans.emplace_back(vec[pos], d[i].second + 1);
        }
    }
    for (auto& x: ans) printf("%d %d\n", x.first, x.second);
    return 0;
}