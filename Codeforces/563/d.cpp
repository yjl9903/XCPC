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
const int maxn = 2000000 + 5;

int n, x, a[maxn];

int main() {
    cin >> n >> x;
    set<int> st, used;
    for (int i = 1; i < (1 << n); i++) st.insert(i);
    int len = 0;
    while (!st.empty()) {
        int tot = *st.begin(); st.erase(st.begin());
        while (used.count(tot ^ x) || tot == x) {
            if (st.empty()) break;
            tot = *st.begin(); st.erase(st.begin());
        }
        if (used.count(tot ^ x) || tot == x) continue;
        a[++len] = tot;
        used.insert(tot);
    }
    printf("%d\n", len);
    for (int i = len; i >= 2; i--) a[i] ^= a[i - 1];
    for (int i = 1; i <= len; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}