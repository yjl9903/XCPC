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

int n, p[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", p + i);
        vector<int> st;
        int tot = 1;
        for (int i = 1; i <= n; i++) {
            st.push_back(p[i]);
            while (!st.empty() && tot == st.back()) {
                st.pop_back(); tot++;
            }
        }
        if (tot == n + 1) puts("1");
        else puts("2");
    }
    return 0;
}