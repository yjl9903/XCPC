#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn]; map<int,int> mp;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), mp[a[i]]++;
    vector<int> v, v2;
    for (auto& x: mp) {
        if (x.second == 1) {
            v.push_back(x.first);
        } else if (x.second == 2) {
            v.push_back(x.first);
            v2.push_back(x.first);
        } else {
            return puts("NO"), 0;
        }
    }
    sort(v.begin(), v.end()); sort(v2.begin(), v2.end()); reverse(v2.begin(), v2.end());
    puts("YES");
    printf("%d\n", (int)v.size());
    for (int& x: v) printf("%d ", x);
    puts("");
    printf("%d\n", (int)v2.size());
    for (int& x: v2) printf("%d ", x);
    return 0;
}