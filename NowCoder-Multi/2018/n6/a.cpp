#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20000 + 5;

int n, a[maxn][20], vis[maxn];
// vector< vector<int> > v[2];
int w[2][maxn][20];

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        ms(vis, 0);
        scanf("%d", &n);
        for (int i = 0; i < (1 << n); i++) for (int j = 0; j < n; j++) scanf("%d", &a[i][j]);
        // v[0].resize(1 << n);
        for (int i = 0; i < (1 << n); i++) {
            // v[0][i].clear();
            // v[0][i].push_back(i);
            w[0][i][0] = i + 1;
            // for (int j = 0; j < n; j++) v[0][i].push_back(a[i][j]);
            for (int j = 0; j < n; j++) w[0][i][j + 1] = a[i][j];
        }
        int tot = 1 << n, t = n, f = 0;
        while (tot > 1){
            // v[f ^ 1].clear();
            for (int i = 0; i < tot; i += 2){
                // printf("%d %d\n", v[f][i].size(), v[f][i + 1].size());
                // sort(v[f][i].begin(), v[f][i].end());
                // sort(v[f][i + 1].begin(), v[f][i + 1].end());
                sort(w[f][i] + 1, w[f][i] + t + 1);
                sort(w[f][i + 1] + 1, w[f][i + 1] + t + 1);
                int flag = 0;
                for (int j = 1; j <= t; j++){
                    if (w[f][i][j] >= w[f][i + 1][t]) {
                        flag = 1;
                        swap(w[f][i][j], w[f][i][t]);
                        // v[f][i].pop_back();
                        // v[f][i].erase(j);
                        // v[f ^ 1].push_back(v[f][i]);
                        memcpy(w[f ^ 1][i / 2], w[f][i], sizeof w[f][i]);
                        break;
                    }
                }
                if (!flag) for (int j = 1; j <= t; j++) {
                    if (w[f][i + 1][j] >= w[f][i][t]) {
                        flag = 2;
                        swap(w[f][i + 1][j], w[f][i + 1][t]);
                        // v[f][i + 1].pop_back();
                        // v[f ^ 1].push_back(v[f][i + 1]);
                        memcpy(w[f ^ 1][i / 2], w[f][i + 1], sizeof w[f][i + 1]);
                        break;
                    }
                }
                // printf(">%d\n", flag);
            }
            tot /= 2; t--; f ^= 1;
            // printf(":%d\n", v[f].size());
        }
        int res = w[f][0][0];
        printf("Case #%d: %d\n", ++kase, res);
    }
    return 0;
}