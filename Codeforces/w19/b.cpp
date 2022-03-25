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

int n, l[maxn], r[maxn];

int main() {
    scanf("%d", &n);
    int sl = 0, sr = 0;
    for (int i = 1; i <= n; i++) scanf("%d%d", l + i, r + i), sl += l[i], sr += r[i];
    int ans = abs(sl - sr), p = 0;
    for (int i = 1; i <= n; i++) {
        if (abs(sl - l[i] + r[i] - (sr - r[i] + l[i])) > ans) {
            ans = abs(sl - l[i] + r[i] - (sr - r[i] + l[i]));
            p = i;
        }
    }
    cout << p << endl;
    return 0;
}