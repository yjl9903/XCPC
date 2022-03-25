#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n; char s[maxn];

string t;
int check(int maxd) {
    t = "";
    int tot = 0, tot2 = 0, mx = 0; string a, b;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '(') {
            if (tot < maxd) {
                tot++; 
                a += '(';
                t += '0';
            } else {
                tot2++; 
                b += '(';
                mx = max(tot2, mx);
                t += '1';
            }
        } else {
            if (tot > 0) {
                tot--; a += ')';
                t += '0';
            } else {
                assert(tot2 >= 0);
                tot2--; 
                b += ')';
                t += '1';
            }
        }
    }
    // cout << a << endl << b << endl;
    return mx <= maxd;
}

int main() {
    scanf("%d%s", &n, s + 1);
    check(2);
    int l = 1, r = n, ans = 0;
    string res;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) res = t, r = m - 1;
        else l = m + 1;
    }
    // cout << ans;
    cout << res;
    return 0;
}