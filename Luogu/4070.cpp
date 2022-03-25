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
const int maxn = 200000 + 5;

int n, a[maxn];
vector<int> lsh;

namespace SAM {
    map<int,int> ch[maxn]; ll cnt = 0;
    int tot, last, link[maxn], len[maxn];
    void clear() {
        tot = last = 1;
    }
    ll insert(int c) {
        int cur = ++tot, p = last;
        len[cur] = len[last] + 1;
        for (; p && !ch[p].count(c); p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; len[nq] = len[p] + 1;
                link[nq] = link[q]; link[q] = link[cur] = nq;
                ch[nq] = ch[q];
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        last = cur;
        return cnt = cnt + len[cur] - len[link[cur]];
    }
}

int main() {
    SAM::clear();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), lsh.push_back(a[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    for (int i = 1; i <= n; i++) {
        ll ans = SAM::insert(lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1);
        printf("%lld\n", ans);
    }
    return 0;
}