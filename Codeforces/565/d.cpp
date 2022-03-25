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
const int maxn = 3000000 + 5;

namespace sieve{
    const int maxp = 3000000 + 5;
    int vis[maxp], prime[maxp], id[maxp], divsor[maxp], tot;
    void init(){
        ms(vis, 0);
        for (int i = 2; i < maxp; i++){
            if (!vis[i]) prime[++tot] = i;
            for (int j = 1; j <= tot && 1ll * prime[j] * i < maxp; j++){
                vis[i * prime[j]] = 1;
                divsor[i * prime[j]] = prime[j];
                if (i % prime[j] == 0) break;
            }
        }
        for (int i = 1; i <= tot; i++) id[prime[i]] = i;
    }
} using namespace sieve;

int n, b[maxn], a[maxn];
multiset<int> st;

int main() {
    init();
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++) {
        scanf("%d", b + i); st.insert(b[i]);
    }
    vector<int> ans;
    while (!st.empty()) {
        int tot = *st.rbegin(); st.erase(st.find(tot));
        if (id[tot]) {
            ans.push_back(id[tot]);
            st.erase(st.find(id[tot]));
        } else {
            ans.push_back(tot);
            st.erase(st.find(tot / divsor[tot]));
        }
    }
    for (int x: ans) printf("%d ", x);
    return 0;
}