#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>
#include <queue>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 30000 + 5;

vector<int> edge[maxn], v;
int ind[maxn], n, m;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        ms(ind, 0); v.clear(); for (int i = 1; i <= n; i++) edge[i].clear();
        while (m--){
            int x, y; scanf("%d%d", &x, &y);
            edge[y].push_back(x); ind[x]++;
        }
        priority_queue<int, vector<int>, less<int> > pq;
        for (int i = 1; i <= n; i++) if (!ind[i]) pq.push(i);
        while (!pq.empty()){
            int t = pq.top(); pq.pop();
            v.push_back(t);
            for (int i = 0; i < edge[t].size(); i++){
                ind[edge[t][i]]--;
                if (!ind[edge[t][i]]) pq.push(edge[t][i]);
            }
        }
        reverse(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++){
            if (i) putchar(' ');
            printf("%d", v[i]);
        }
        puts("");
    }
    return 0;
}