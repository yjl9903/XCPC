#include <iostream>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

struct edge{
    int to, nxt;
}line[maxn];
int head[maxn] = {0}, cnt = 0;
void add(int x, int y){
    line[++cnt].to = y;
    line[cnt].nxt = head[x];
    head[x] = cnt;
}
int n, k, tag[maxn];
vector<PII> v;

void dfs(int p, int d){
    v.push_back(make_pair(p, d));
    vector<int> c;
    for (int i = head[p]; i; i = line[i].nxt){
        int v = line[i].to;
        c.push_back(v);
    }
    for (int i = c.size() - 1; i >= 0; i--){
        dfs(c[i], d + 1);
    }
}

int main(){
    scanf("%d %d", &n, &k);
    for (int i = 2; i <= n; i++){
        int x; 
        scanf("%d", &x);
        add(x, i);
    }
    dfs(1, 0);
    for (int i = 0; i < v.size(); i++){
        tag[v[i].first] = i;
    }
    // for (int i = 0; i < v.size(); i++) cout << v[i].first << ' '; cout << endl;
    while (k--){
        int u, ki, res = -1; 
        // cin >> u >> ki;
        scanf("%d%d", &u, &ki);
        // for (int i = 0; i < v.size(); i++) if (u == v[i].first){
            int i = tag[v[i].first];
            int j = 1, d = v[i].second; 
            if (ki == 1){
                res = u; break;
            }
            i++;
            for (; j < ki && /* v[i].second > d && */ i < v.size(); j++){
                i++;
            }
            i--;
            // cout << i << endl;
            if (j == ki && i < v.size() && v[i].second > d){
                res = v[i].first;
            }
            break;
        // }
        printf("%d\n", res);
    }
    return 0;
}