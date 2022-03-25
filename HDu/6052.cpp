#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100 + 5;

int n, m, map[maxn][maxn];
vector<PII> v[maxn * maxn];

int b[maxn]; vector<int> y[maxn];
ll cal(int c){
    ms(b, 0); for (int i = 1; i <= n; i++) y[i].clear();
    ll ans = 0;
    for (auto& t : v[c]){
        int ni = t.first, nj = t.second;
        // for (int i = 1; i <= m; i++) y[i].clear();
        for (int i = 1; i <= m; i++) if (b[i]) y[b[i]].push_back(i), b[i] = 0;
        int l = 1, r = m; vector<int>::iterator it;
        for (int i = ni, flag = 0; i >= 1; i--){
            for (it = y[i].begin(); it != y[i].end(); it++){
                int t = *it;
                if (t < nj) l = max(l, t + 1);
                else if (t > nj) r = min(r, t - 1);
                else {
                    flag = 1; break;
                }
            }
            if (flag) break;
            ans += (n - ni + 1) * (nj - l + 1) * (r - nj + 1);
        }
        b[nj] = ni;
    }
    return ans;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n * m; i++) v[i].clear();
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            scanf("%d", &map[i][j]);
            v[map[i][j]].emplace_back(i, j);
        }
        ll ans = 0;
        for (int i = 0; i <= n * m; i++) if (v[i].size()){
            sort(v[i].begin(), v[i].end());
            ans += cal(i);
        }
        printf("%.9lf\n", ans * 4.0 / (1.0 * n * (n + 1) * m * (m + 1)));
    }
    return 0;
}