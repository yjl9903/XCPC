#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, a[maxn];

int main() {
    cin >> n;
    set<int> s;
    for (int i = 1; i <= n - 1; i++) s.insert(i);
    for (int i = 2; i <= n; i++) {
        int tot = 0;
        for (int j = i; j <= n; j += i) {
            if (a[j]) continue;
            if (tot == 0) {
                tot = *s.begin(); s.erase(s.begin());
            }
            a[j] = tot;
        }
    }
    for (int i = 2; i <= n; i++) printf("%d ", a[i]);
    return 0;
}