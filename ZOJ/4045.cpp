#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct edge{int to, next;}f[2 * maxn];
int n, k, vis[maxn], head[maxn], cnt = 0, flag = 0;
int num = 0;
vector<int> res[maxn];
stack<int> s;

void add(int x, int y){
    f[++cnt].to = y;
    f[cnt].next = head[x];
    head[x] = cnt;
}

int dfs(int p){
    // cout << p << endl;
    int sum = 1, mark = 1;
    for (int i = head[p]; i; i = f[i].next){
        int v = f[i].to;
        if (!vis[v]){
            vis[v] = 1;
            s.push(v);
            sum += dfs(v);
        }
        
        if (sum == k && mark){
            int v;
            res[num].clear();
            for (int i = 0; i < k; i++){
                v = s.top(); s.pop();
                // bel[v] = num;
                res[num].push_back(v);
            }
            mark = 0;
            num++;
            sum = 0;
        }
    }
    return mark ? sum : 0;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        cnt = 0; num = 0; ms(vis, 0); ms(head, 0);
        // for (int i = 0; i < maxn; res[i++].clear());
        scanf("%d%d", &n, &k);
        for (int i = 0, a, b; i < n - 1; i++){
            scanf("%d%d", &a, &b);
            add(a, b); add(b, a);
        }
        
        vis[1] = 1; s.push(1);
        dfs(1);
        
        // for (int i = 1; i <= n; cout << bel[i++] << ' '); cout << endl << num << endl;

        flag = 0;
        for (int i = 0; i < num; i++){
            if (res[i].size() != k){
                flag = 1; break;
            }
            // sort(res[i].begin(), res[i].end());
        }
        if (num != n / k) flag = 1;

        if (flag)   printf("NO\n");
        else {
            printf("YES\n");
            for (int i = 0; i < num; i++){
                for (int j = 0; j < res[i].size(); j++){
                    if (j) printf(" ");
                    printf("%d", res[i][j]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}