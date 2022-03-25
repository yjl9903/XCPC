#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;
const int maxm = 100 + 5;

vector<PII> v;
int n, m, k;

int b[maxn]; vector<int> y[maxn];
ll cal(){
    ms(b, 0); ll ans = 0;
    for (int i = 1; i <= n; i++) y[i].clear();
    for (auto& t : v){
        int ni = t.first, nj = t.second;
        for (int i = 1; i <= m; i++) if (b[i]) y[b[i]].push_back(i), b[i] = 0;
        int l = 1, r = m, flag = 0; vector<int>::iterator it;
        for (int i = ni; i >= 1; i--){
            for (it = y[i].begin(); it != y[i].end(); it++){
                int t = *it;
                if (t < nj) l = max(l, t + 1);
                else if (t > nj) r = min(r, t - 1);
                else {
                    flag = 1; break;
                }
            }
            if (flag) break;
            ans += 1ll * (n - ni + 1) * (nj - l + 1) * (r - nj + 1);
        }
        b[nj] = ni;
    }
    return ans;
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &n, &m, &k);
        int x, y; v.clear();
        while (k--) scanf("%d%d", &x, &y), v.emplace_back(x, y);
        sort(v.begin(), v.end());
        printf("Case #%d: %lld\n", ++kase, 1ll * n * (n + 1) * m * (m + 1) / 4 - cal());
    }
    return 0;
}