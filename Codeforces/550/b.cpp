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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, a[maxn], sum = 0;
vector<int> v[2];

bool cmp(int x, int y) { return x > y; }

int cal(vector<int> v1, vector<int> v2) {
    int ans = sum;
    for (int& x: v1) {
        ans -= x;
        if (v2.empty()) break;
        ans -= v2.back(); v2.pop_back();
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        v[a[i] % 2].push_back(a[i]);
        sum += a[i];
    }
    sort(v[0].begin(), v[0].end(), cmp); sort(v[1].begin(), v[1].end(), cmp);
    cout << min(cal(v[0], v[1]), cal(v[1], v[0]));
    return 0;
}