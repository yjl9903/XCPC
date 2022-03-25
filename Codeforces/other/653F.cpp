#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int pos[maxn << 1];
namespace sam {
    int tot, last, len[maxn << 1], link[maxn << 1], ch[maxn << 1][2];
    void clear() { 
        ms(ch, 0); tot = last = 1; 
    }
    void insert(int c, int i) {
        int cur = ++tot, p = last;
        len[cur] = len[last] + 1;
        pos[cur] = i;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; len[nq] = len[p] + 1; pos[nq] = pos[q];
                link[nq] = link[q]; link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        } 
        last = cur;
    }
}
using namespace sam;

int n, lft[maxn], pre[maxn];
char s[maxn];

int main() {
    sam::clear();
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '(') sam::insert(0, i);
        else sam::insert(1, i);
    }
    map<int,vector<int> > mp;
    mp[0].push_back(0);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1];
        if (s[i] == '(') pre[i]++;
        else pre[i]--;
        mp[pre[i]].push_back(i);
    }
    vector<int> stk;
    for (int i = n; i >= 1; i--) {
        while (!stk.empty() && pre[i] < pre[stk.back()]) {
            int x = stk.back(); stk.pop_back();
            lft[x] = i;
        }
        stk.push_back(i);
    }
    ll ans = 0;
    for (int u = 1; u <= tot; u++) {
        int p = pos[u];
        int l = max(lft[p] + 1, pos[u] - len[u] + 1);
        int r = pos[u] - len[link[u]];
        if (l <= r) {
            auto& v = mp[pre[p]];
            ans += upper_bound(v.begin(), v.end(), r - 1) - lower_bound(v.begin(), v.end(), l - 1);
        }
    }
    cout << ans;
    return 0;
}