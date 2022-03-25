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
const int maxn = 1000000 + 5;

int cal(int x) {
    int ans = 0;
    while (x) ans += (x % 10) * (x % 10), x /= 10;
    return ans;
}
int ans[maxn], n;
int check(int x) {
    if (x == 0) return 1;
    int r = x;
    set<int> st; st.insert(x);
    while (1) {
        x = cal(x);
        if (x < r) {
            if (ans[x]) return 1;
            else return 0;
        }
        if (x == 1) return 1;
        if (st.count(x)) return 0;
        st.insert(x);
    }
    return 0;
}

int main() {
    vector<int> v;
    for (int i = 1; i < maxn; i++) {
        ans[i] = check(i);
        if (ans[i]) v.push_back(i);
        if ((int)v.size() == 150000) break;
    }
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        printf("%d\n", v[n - 1]);
    }
    return 0;
}