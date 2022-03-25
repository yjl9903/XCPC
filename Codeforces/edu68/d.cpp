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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, k;

map<int,int> sg;
int dfs(int u) {
    if (sg.count(u)) return sg[u];
    if (u < k) return k % 3 != 0;
    int f1 = dfs(u - 1), f2 = dfs(u - 2), f3 = dfs(u - k);
    if (!f1 || !f2 || !f3) return sg[u] = 1;
    return sg[u] = 0;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        if (k > n) {
            if (n % 3 == 0) puts("Bob");
            else puts("Alice");
        } else if (k == n) {
            puts("Alice");
        } else {
            // sg.clear();
            // sg[0] = 0; sg[1] = 1; sg[2] = 1; sg[k] = 1;
            // if (dfs(n)) puts("Alice");
            // else puts("Bob");
            if (k % 3 == 0) {
                int x = n % (k + 1);
                if (x == k) puts("Alice");
                else {
                    if (x % 3 == 0) puts("Bob");
                    else puts("Alice");
                }
            } else if (k % 3 == 1) {
                if (n % 3 == 0) puts("Bob");
                else puts("Alice");
            } else {
                if (n % 3 == 0) puts("Bob");
                else puts("Alice");
            }
        }
    }
    return 0;
}