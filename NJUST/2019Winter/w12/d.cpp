#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

const int maxp = 100000 + 5;
int vis[maxp], prime[maxp], tot;
void init(){
    ms(vis, 0);
    for (int i = 2; i < maxp; i++){
        if (!vis[i]) prime[tot++] = i;
        for (int j = 0; j < tot && prime[j] * i < maxp; j++){
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int n, a[200];

int main() {
    init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int res = 0;
    for (int i = 0; i < tot; i++) {
        set<int> st; int p = prime[i];
        for (int j = 1; j <= n; j++) {
            int c = 0;
            while (a[j] % p == 0) a[j] /= p, c++;
            if (c) st.insert(c);
        }
        // cout << (int)st.size() << endl;
        if ((int)st.size() % 2 == 1) res++;
    }
    // cout << res << endl;
    set<int> st;
    for (int i = 1; i <= n; i++) if (a[i] > 1) st.insert(a[i]);
    res += (int)st.size();
    // cout << res << endl;
    if (res % 2 == 0) puts("Arpa");
    else puts("Mojtaba");
    return 0;
}