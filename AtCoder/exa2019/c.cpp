#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, q;
char s[maxn], t[maxn], d[maxn];

int check(int x) {
    int tot = x;
    for (int i = 1; i <= q; i++) {
        if (t[i] == s[tot]) {
            if (d[i] == 'L') tot--;
            else tot++;
            if (tot == 0) return 1;
            else if (tot == n + 1) return -1;
        }
    }
    return 0;
}

int main() {
    scanf("%d%d%s", &n, &q, s + 1);
    for (int i = 1; i <= q; i++) {
        char tmp1[3], tmp2[3]; scanf("%s%s", tmp1, tmp2);
        t[i] = tmp1[0]; d[i] = tmp2[0];
    }
    int l = 1, r = n, ans1 = 0, ans2 = n + 1;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (check(m) == 1) l = m + 1, ans1 = m;
        else r = m - 1;
    }
    l = 1, r = n;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (check(m) == -1) r = m - 1, ans2 = m;
        else l = m + 1;
    }
    cout << n - ans1 - (n - ans2 + 1) << endl;
    return 0;
}