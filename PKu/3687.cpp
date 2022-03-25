#include <cstdio>
#include <cstring>
#include <functional>
#include <queue>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;

int n, m, ind[maxn], ans[maxn];
vector<int> edge[maxn], v;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        v.clear(); ms(ind, 0);
        for (int i = 0; i <= n; i++) edge[i].clear();
        int flag = 0;
        while (m--){
            int x, y; scanf("%d%d", &x, &y);
            // if (x == y) flag = 1;
            ind[x]++; edge[y].push_back(x);
        }
        if (flag){
            puts("-1");
            continue;
        }
        priority_queue<int, vector<int>, less<int> > pq;
        for (int i = 1; i <= n; i++) if (!ind[i]) pq.push(i);
        int cnt = n;
        while (!pq.empty()){
            int t = pq.top(); pq.pop();
            // v.push_back(t);
            ans[t] = cnt--;
            for (int i = 0; i < edge[t].size(); i++){
                ind[edge[t][i]]--;
                if (!ind[edge[t][i]]) pq.push(edge[t][i]);
            }
        }
        if (cnt){
            puts("-1");
            continue;
        }
        reverse(v.begin(), v.end());
        for (int i = 1; i <= n; i++){
            if (i > 1) putchar(' ');
            printf("%d", ans[i]);
        }
        puts("");
    }
    return 0;
}